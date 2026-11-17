"""Run from the VOD checkout, passing the configured CMake build directory."""

import json
from pathlib import Path
import shlex
import subprocess
import sys
import tempfile


def main():
    build = Path(sys.argv[1] if len(sys.argv) > 1 else "build").resolve()
    tests = json.loads(subprocess.check_output(
        ["ctest", "--test-dir", str(build), "--show-only=json-v1"], text=True
    ))["tests"]
    (test,) = [test for test in tests if test["name"] == "vod_session_mysql_integration"]
    command = test["command"]
    (job_slot,) = [i for i, arg in enumerate(command) if Path(arg).name == "vod_job_store_test"]
    original_job_test = command[job_slot]
    cache = {}
    for line in (build / "CMakeCache.txt").read_text().splitlines():
        if not line or line.startswith(("#", "//")) or "=" not in line:
            continue
        key_and_type, value = line.split("=", 1)
        cache[key_and_type.split(":", 1)[0]] = value
    project = Path(cache["CMAKE_HOME_DIRECTORY"])
    source = Path(__file__).with_name("13_VOD_租约重领测试.cpp")

    with tempfile.TemporaryDirectory(prefix="vod-lease-case-") as temp:
        executable = Path(temp) / "lease_reclaim_test"
        subprocess.run([
            cache["CMAKE_CXX_COMPILER"], "-std=c++17", "-pthread",
            "-I", str(project / "include"), "-I", cache["MYSQL_INCLUDE_DIR"],
            str(source), str(project / "src/transcode/job_store.cpp"),
            cache["MYSQL_LIBRARY"], cache["OPENSSL_CRYPTO_LIBRARY"],
            "-o", str(executable),
        ], check=True, timeout=60)
        wrapper = Path(temp) / "job_store_tests"
        wrapper.write_text(
            "#!/bin/sh\nset -e\n"
            f"{shlex.quote(original_job_test)}\n"
            f"exec {shlex.quote(str(executable))}\n"
        )
        wrapper.chmod(0o700)
        command[job_slot] = str(wrapper)
        subprocess.run(command, cwd=build, check=True, timeout=240)


if __name__ == "__main__":
    main()
