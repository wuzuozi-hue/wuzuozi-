"""2026-10-27: change PAYLOAD to observe the C++ request-validation path."""
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

# 只修改这里：这就是发送给 POST /v1/questions 的 JSON 正文。
PAYLOAD = {
    "question": "什么是 RAII？",
    "document_ids": ["962bf7f3-8c8c-4090-9234-b5d103420156"]
}
def main():
    sys.stdout.reconfigure(encoding="utf-8")
    settings = local_env()
    key = settings.get("API_KEY")
    if not key:
        raise SystemExit("Local API_KEY is missing; inspect the project's .env locally.")
    try:
        with httpx.Client(timeout=10, trust_env=False) as client:
            response = client.post(
                "http://127.0.0.1:18880/v1/questions",
                headers={"X-API-Key": key},
                json=PAYLOAD,
            )
    except httpx.RequestError as error:
        raise SystemExit(f"Request failed: {type(error).__name__}. Check the local service.") from None
    print("Request JSON:", json.dumps(PAYLOAD, ensure_ascii=False))
    print("HTTP status:", response.status_code)
    try:
        print("Response JSON:", json.dumps(response.json(), ensure_ascii=False, indent=2))
    except ValueError:
        print("Response is not JSON.")


if __name__ == "__main__":
    main()
