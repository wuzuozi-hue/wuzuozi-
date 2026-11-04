-- PostgreSQL 隔离练习：临时表仅用于设计验证，不修改项目数据。
BEGIN;

CREATE TEMP TABLE practice_jobs (
    id TEXT PRIMARY KEY
);

-- TODO：创建临时表 practice_requests，包含：
CREATE TEMP TABLE practice_requests(
    request_key TEXT PRIMARY KEY,
    request_hash TEXT NOT NULL,
    job_id TEXT NOT NULL REFERENCES practice_jobs(id)
);
-- request_key：请求键，文本，主键（保证唯一且非空）

-- request_hash：请求内容摘要，文本，不能为空
-- job_id：关联任务 ID，文本，不能为空，引用 practice_jobs(id)

-- 创建表后可以用如下语句测试。
INSERT INTO practice_jobs(id) VALUES ('J1');
INSERT INTO practice_requests(request_key, request_hash, job_id)
VALUES ('key-1', 'hash-A', 'J1');
SELECT request_key, request_hash, job_id FROM practice_requests;

ROLLBACK;
