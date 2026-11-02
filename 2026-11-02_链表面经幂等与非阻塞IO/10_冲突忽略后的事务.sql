-- PostgreSQL 临时表实验，不修改项目表。
CREATE TEMP TABLE practice_jobs_skip (id text PRIMARY KEY);
CREATE TEMP TABLE practice_keys_skip (
    request_key text PRIMARY KEY,
    job_id text NOT NULL REFERENCES practice_jobs_skip(id)
);
INSERT INTO practice_jobs_skip(id) VALUES ('J1');
INSERT INTO practice_keys_skip(request_key, job_id) VALUES ('key-1', 'J1');

BEGIN;
-- TODO 1：在事务中插入任务 J2。
INSERT INTO practice_jobs_skip(id) VALUES ('J2');
INSERT INTO practice_keys_skip(request_key, job_id) VALUES ('key-1', 'J2')
ON CONFLICT(request_key) DO NOTHING
RETURNING request_key,job_id;
-- TODO 2：尝试插入映射 key-1 -> J2，
-- 使用 ON CONFLICT (request_key) DO NOTHING RETURNING request_key, job_id。

-- 本次故意不检查冲突，直接提交；观察副作用。
COMMIT;
SELECT id FROM practice_jobs_skip ORDER BY id;
SELECT request_key, job_id FROM practice_keys_skip ORDER BY request_key;
