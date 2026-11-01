-- PostgreSQL 独立实验：只使用临时表，最后回滚，不修改项目表。
BEGIN;

CREATE TEMP TABLE practice_terminal_jobs (
    id text PRIMARY KEY,
    status text NOT NULL,
    error text NOT NULL DEFAULT ''
);

INSERT INTO practice_terminal_jobs(id, status) VALUES
    ('J1', 'running'),
    ('J2', 'failed');

-- TODO 1：当 J1 当前是 running 时，将其改为 failed，error 改为 job_timeout。
-- 用 RETURNING id, status, error 查看实际更新的行。
UPDATE practice_terminal_jobs
SET status = 'failed',error = 'job_timeout'
WHERE id ='J1' AND status = 'running'
RETURNING id,status,error;
-- TODO 2：把同一条条件更新再执行一次。
-- 想一想：第二次还能匹配到 status = 'running' 的 J1 吗？
UPDATE practice_terminal_jobs
SET status = 'failed',error = 'job_timeout'
WHERE id ='J1' AND status = 'running'
RETURNING id,status,error;
-- 查看最终状态。
SELECT id, status, error FROM practice_terminal_jobs ORDER BY id;

ROLLBACK;
