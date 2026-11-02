-- PostgreSQL 临时表实验；最后回滚，不修改项目数据。
-- 仅验证唯一约束和冲突行为；不实现完整请求幂等或任务事务。
BEGIN;

CREATE TEMP TABLE practice_idempotency (
    request_key text PRIMARY KEY,
    job_id text NOT NULL,
    question text NOT NULL
);

INSERT INTO practice_idempotency (request_key, job_id, question)
VALUES ('key-1', 'J1', '什么是 RAII？');

INSERT INTO practice_idempotency(request_key,job_id,question)
VALUES ('key-1','J2','什么是 RAII？')
ON CONFLICT(request_key) DO NOTHING
RETURNING request_key,job_id;
-- TODO：模拟同一个请求重试，尝试插入 key-1、J2 和相同问题。
-- 使用 ON CONFLICT (request_key) DO NOTHING，
-- 再用 RETURNING request_key, job_id 查看是否插入了新行。

-- 查看数据库中最终记录。
SELECT request_key, job_id, question FROM practice_idempotency ORDER BY request_key;
ROLLBACK;
