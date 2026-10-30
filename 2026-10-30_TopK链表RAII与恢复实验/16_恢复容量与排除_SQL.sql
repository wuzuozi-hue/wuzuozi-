-- 在临时表practice_jobs里查询恢复候选：
-- 只选status='queued'，排除已经加载J1和正在提交J4。
-- 返回id和age_seconds；按created_at、id升序；最多返回2行。
-- 只写一条SELECT；驱动负责临时表和数据。
SELECT id,age_seconds
FROM practice_jobs
WHERE status = 'queued' AND id NOT IN('J1','J4')
ORDER BY created_at ASC, id ASC
LIMIT 2;
