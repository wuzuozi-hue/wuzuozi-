-- 2026-10-19 PostgreSQL 练习：条件更新与 RETURNING
-- 只在临时表 practice_jobs 上练习；一次执行完整脚本，观察两次更新的差别。

CREATE TEMP TABLE practice_jobs (
    id TEXT PRIMARY KEY,
    status TEXT NOT NULL CHECK (status IN ('queued', 'running', 'succeeded', 'failed'))
);

INSERT INTO practice_jobs (id, status) VALUES
    ('J1', 'queued'),
    ('J2', 'succeeded');

-- 首次领取 J1：queued -> running，返回更新到的行。
UPDATE practice_jobs
SET status ='running'
WHERE id = 'J1' AND status ='queued'
RETURNING id,status;
-- 再次尝试领取 J1：旧状态不再是 queued，返回 0 行。
UPDATE practice_jobs
SET status ='running'
WHERE id = 'J1' AND status ='queued'
RETURNING id,status;
-- 确认 J1 仍存在，状态为 running。
SELECT id,status
FROM practice_jobs
WHERE id ='J1' AND status = 'running';
