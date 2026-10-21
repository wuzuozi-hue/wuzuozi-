-- 目标：两个 worker 同时尝试认领 J1，只有一个能把它从 queued 改为 running。
-- PostgreSQL 练习；当前文件用于手写与推演，尚未在数据库执行。

-- 初始数据：
-- id | status
-- J1 | queued

-- 练习 1：补全条件更新。
-- 要求：只在 J1 仍是 queued 时改为 running，并返回成功更新的 id。
UPDATE practice_jobs
SET status = 'running'
WHERE id = 'J1' AND status = 'queued'
RETURNING id;

-- 练习 2：假设 worker A 先执行成功，worker B 随后执行同一语句。
-- A 返回几行？B 返回几行？J1 最终是什么状态？
-- A：1
-- B：0
-- 最终状态：running

-- 练习 3：如果 worker A 拿到 J1 后崩溃，这条 SQL 本身能让任务重新排队吗？
-- 答：不能 直接失败了
