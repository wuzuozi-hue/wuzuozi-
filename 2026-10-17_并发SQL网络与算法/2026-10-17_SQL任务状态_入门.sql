-- 2026-10-17 SQL 入门：读任务状态、按条件更新状态
-- 这是独立练习表 practice_jobs，不操作 DevDocQA 的 jobs 表。
-- 先写 SQL，再一起验证；不要在生产数据库中运行练习脚本。

CREATE TEMP TABLE practice_jobs (
    id TEXT PRIMARY KEY,
    status TEXT NOT NULL CHECK (status IN ('queued', 'running', 'succeeded', 'failed'))

);

INSERT INTO practice_jobs (id, status) VALUES
    ('J1', 'queued'),
    ('J2', 'succeeded'),
    ('J3', 'queued');

-- TODO 1：只查询状态为 queued 的任务，显示 id 和 status。
SELECT  id, status
FROM practice_jobs
WHERE status = 'queued';
-- TODO 2：只在 J1 仍为 queued 时，把它改为 running。
UPDATE practice_jobs
SET status ='running'
WHERE id ='J1' AND status = 'queued';

-- TODO 3：查询所有任务的 id 和 status，按 id 排序，检查更新结果。
SELECT id,status
FROM practice_jobs
ORDER BY id;

UPDATE practice_jobs
SET status = 'failed'
WHERE id ='J1' AND status ='running';

SELECT id,status
FROM practice_jobs
WHERE id = 'J1';
