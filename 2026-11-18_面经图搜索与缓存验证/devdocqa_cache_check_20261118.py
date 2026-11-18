import json
import os
import secrets
import socket
import subprocess
import sys
import tempfile
from contextlib import ExitStack
from pathlib import Path
from threading import Thread
from time import monotonic, sleep

import httpx
import psycopg
import redis
from fakeredis import TcpFakeServer


workspace = Path(__file__).resolve().parent.parent
project = workspace / "outputs/devdocqa"
native = workspace / "work/devdocqa-build"
bin_dir = native / "msys/ucrt64/bin"
flags = getattr(subprocess, "CREATE_NO_WINDOW", 0)


def local_port():
    with socket.socket() as sock:
        sock.bind(("127.0.0.1", 0))
        return sock.getsockname()[1]


def wait_for(probe, timeout=12):
    deadline = monotonic() + timeout
    while monotonic() < deadline:
        try:
            result = probe()
            if result:
                return result
        except httpx.TransportError:
            pass
        sleep(0.1)
    raise TimeoutError("Experiment checkpoint did not become ready")


def stop(process):
    if process.poll() is None:
        process.terminate()
        try:
            process.wait(timeout=5)
        except subprocess.TimeoutExpired:
            process.kill()
            process.wait(timeout=5)


def experiment(report_path):
    with tempfile.TemporaryDirectory(prefix="devdocqa-cache-") as directory, ExitStack() as cleanup:
        temporary = Path(directory)
        data_dir = temporary / "documents"
        data_dir.mkdir()
        pgdata = temporary / "pgdata"
        pg_port, worker_port, api_port = local_port(), local_port(), local_port()
        assert len({pg_port, worker_port, api_port}) == 3
        dsn = f"host=127.0.0.1 port={pg_port} user=docqa dbname=postgres"
        api_key = secrets.token_urlsafe(24)
        env = os.environ.copy()
        env["PATH"] = str(bin_dir) + os.pathsep + env["PATH"]
        env.update(API_KEY=api_key, INTERNAL_KEY=secrets.token_urlsafe(24), PG_DSN=dsn,
                   DOCQA_PORT=str(api_port), DOCQA_BIND="127.0.0.1", WORKER_PORT=str(worker_port),
                   AI_SERVICE_URL=f"http://127.0.0.1:{worker_port}", MODEL_MODE="mock",
                   MODEL_SIGNATURE="mock:featurehash-v1;extractive-v1;chunk-v1",
                   EMBEDDING_SIGNATURE="mock:featurehash-v1", DATA_DIR=str(data_dir),
                   STATIC_DIR=str(project / "web"), CACHE_TTL_SECONDS="600",
                   REDIS_HOST="127.0.0.1", RATE_LIMIT_PER_MINUTE="60")

        def pg_ctl(*args, check=True):
            subprocess.run([str(bin_dir / "pg_ctl.exe"), "-D", str(pgdata), *args],
                           env=env, creationflags=flags, check=check, timeout=25)

        subprocess.run([str(bin_dir / "initdb.exe"), "-D", str(pgdata), "--auth=trust",
                        "--encoding=UTF8", "--no-locale", "-U", "docqa"], env=env,
                       creationflags=flags, stdout=subprocess.DEVNULL, check=True, timeout=30)
        pg_ctl("-l", str(temporary / "postgres.log"), "-o", f"-h 127.0.0.1 -p {pg_port}", "-w", "start")
        cleanup.callback(pg_ctl, "-m", "fast", "-w", "stop", check=False)
        db = cleanup.enter_context(psycopg.connect(dsn, autocommit=True))
        for filename in ("001_initial.sql", "002_embedding_signature.sql"):
            db.execute((project / "db" / filename).read_text(encoding="utf-8"))

        redis_server = TcpFakeServer(("127.0.0.1", 0), server_version=(7, 4))
        redis_server.daemon_threads = True
        Thread(target=redis_server.serve_forever, daemon=True).start()
        cleanup.callback(redis_server.server_close)
        cleanup.callback(redis_server.shutdown)
        redis_port = redis_server.server_address[1]
        env["REDIS_PORT"] = str(redis_port)
        cache = cleanup.enter_context(redis.Redis(host="127.0.0.1", port=redis_port))

        def launch(name, command, cwd):
            log_path = temporary / f"{name}.log"
            log = cleanup.enter_context(log_path.open("wb"))
            process = subprocess.Popen(command, cwd=cwd, env=env, stdout=log,
                                       stderr=subprocess.STDOUT, creationflags=flags)
            cleanup.callback(stop, process)
            return process

        worker = launch("worker", [sys.executable, "-m", "app"], project / "worker")
        backend = launch("backend", [str(native / "backend-clang/devdocqa.exe")], project)
        client = cleanup.enter_context(httpx.Client(base_url=f"http://127.0.0.1:{api_port}",
                                                   headers={"X-API-Key": api_key}, trust_env=False))

        def ready():
            for name, process in (("worker", worker), ("backend", backend)):
                if process.poll() is not None:
                    log = (temporary / f"{name}.log").read_text(encoding="utf-8", errors="replace")
                    raise RuntimeError(f"{name} exited: {log[-1200:]}")
            return client.get("/ready").status_code == 200

        def complete(job_id):
            status = client.get(f"/v1/jobs/{job_id}").raise_for_status().json()["status"]
            if status == "failed":
                raise RuntimeError("Experiment job failed")
            return status == "succeeded"

        def upload(name, content):
            accepted = client.post("/v1/documents", files={"file": (name, content.encode())})
            assert accepted.status_code == 202, accepted.text
            body = accepted.json()
            wait_for(lambda: complete(body["job_id"]))
            return body["document_id"]

        def ask():
            accepted = client.post("/v1/questions", json=request)
            assert accepted.status_code == 202, accepted.text
            body = accepted.json()
            wait_for(lambda: complete(body["job_id"]))
            version = db.execute("SELECT version FROM collection_state WHERE id=1").fetchone()[0]
            key = db.execute("SELECT payload->>'cache_key' FROM jobs WHERE id=%s",
                             (body["job_id"],)).fetchone()[0]
            return {"cached": body["cached"], "version": version, "key": key}

        wait_for(ready)
        first_doc = upload("raii.md", "RAII 将资源生命周期绑定到对象，析构时自动释放资源。")
        request = {"question": "RAII 如何通过对象析构释放资源？", "document_ids": [first_doc]}
        first = ask()
        wait_for(lambda: cache.exists(first["key"]))
        second = ask()
        upload("http.md", "HTTP 是应用层协议，请求包含方法、路径与头部。")
        third = ask()
        old_ttl = cache.ttl(first["key"])
        assert [record["cached"] for record in (first, second, third)] == [False, True, False]
        assert first["version"] == second["version"] and third["version"] == second["version"] + 1
        assert first["key"] == second["key"] and third["key"] != first["key"] and old_ttl > 0
        results = {"database": "isolated PostgreSQL with pgvector", "redis": "fakeredis TCP test double",
                   "model": "mock", "requests": [first, second, third], "previous_key_ttl_seconds": old_ttl}
        report_path.write_text(json.dumps(results, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
        print(json.dumps(results, ensure_ascii=False))


if __name__ == "__main__":
    experiment(Path(sys.argv[1]))
