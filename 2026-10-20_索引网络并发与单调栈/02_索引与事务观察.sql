-- 2026-10-20：PostgreSQL 独立练习。仅创建会话内临时表，不改 DevDocQA 正式 jobs 表。
-- 先预测，再执行；索引是否被采用，以实际 EXPLAIN 结果为准。
CREATE TEMP TABLE practice_jobs (
    id integer PRIMARY KEY,
    status text NOT NULL,
    created_at timestamp NOT NULL
);

INSERT INTO practice_jobs(id, status, created_at) VALUES
    (1, 'queued', '2026-10-20 10:00:00'),
    (2, 'running', '2026-10-20 10:01:00'),
    (3, 'queued', '2026-10-20 10:02:00');

CREATE INDEX practice_jobs_status_created_idx ON practice_jobs(status, created_at);

EXPLAIN (ANALYZE, BUFFERS)
SELECT id, status FROM practice_jobs
WHERE status = 'queued'
ORDER BY created_at
LIMIT 10;

-- 事务练习：先预测事务内的结果与回滚后的结果。
BEGIN;
UPDATE practice_jobs SET status = 'running'
WHERE id = 1 AND status = 'queued';
SELECT id, status FROM practice_jobs WHERE id = 1;
ROLLBACK;
SELECT id, status FROM practice_jobs WHERE id = 1;
