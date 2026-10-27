"""2026-10-27: use GET to inspect an existing job; no question is submitted."""
import json
import os
import sys
from pathlib import Path

import httpx

def locate_project():
    explicit = os.environ.get("DEVDOCQA_ROOT")
    if explicit:
        candidate = Path(explicit).expanduser().resolve()
        if (candidate / "scripts" / "smoke_test.py").is_file():
            return candidate
        raise SystemExit("DEVDOCQA_ROOT must point to the existing DevDocQA project.")
    for parent in Path(__file__).resolve().parents:
        for candidate in (parent / "outputs" / "devdocqa", parent / "devdocqa"):
            if (candidate / "scripts" / "smoke_test.py").is_file():
                return candidate
    raise SystemExit("Set DEVDOCQA_ROOT to the existing DevDocQA project path.")


PROJECT = locate_project()
sys.path.insert(0, str(PROJECT / "scripts"))
from smoke_test import local_env

# 查询同一个任务时保留这个 ID；只有提交新问题后才换成新 ID。
JOB_ID = "d0ee28d0-11b2-494b-9614-c6440b745562"


def main():
    sys.stdout.reconfigure(encoding="utf-8")
    key = local_env().get("API_KEY")
    if not key:
        raise SystemExit("Local API_KEY is missing.")
    try:
        with httpx.Client(timeout=10, trust_env=False) as client:
            response = client.get(
                f"http://127.0.0.1:18880/v1/jobs/{JOB_ID}",
                headers={"X-API-Key": key},
            )
    except httpx.RequestError as error:
        raise SystemExit(f"Request failed: {type(error).__name__}. Check the local service.") from None
    print("Method: GET")
    print("Job ID:", JOB_ID)
    print("HTTP status:", response.status_code)
    try:
        print("Response JSON:", json.dumps(response.json(), ensure_ascii=False, indent=2))
    except ValueError:
        print("Response is not JSON.")


if __name__ == "__main__":
    main()
