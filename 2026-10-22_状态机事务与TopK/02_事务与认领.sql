-- 2026-10-22：SQL 事务与条件认领练习。
-- 先纸上推演；只有在实际连接 PostgreSQL 并执行后，才记录为实测。
-- 练习表假定为 practice_jobs(id TEXT PRIMARY KEY, status TEXT NOT NULL)。

-- 情景：J1 初始为 queued。Worker A 和 Worker B 同时尝试认领。
-- TODO 1：写一条 UPDATE，只在 J1 仍为 queued 时改成 running，并返回 id。
UPDATE practice_jobs
SET status = running
WHERE id = 'J1' AND status = 'queued'
RETURNING id;
-- TODO 2：推演 A 成功后，B 再执行同一语句会返回几行？为什么？

-- TODO 3：假设还要写一条 audit 日志。把“认领任务”和“写日志”放在
--         一个事务里；若日志插入失败，两条写入最后应是什么结果？

-- 注意：DevDocQA 的真实表是 outputs/devdocqa/db/001_initial.sql 中的 jobs。
-- 本文件是隔离的学习练习，不表示项目已采用这段 SQL。
