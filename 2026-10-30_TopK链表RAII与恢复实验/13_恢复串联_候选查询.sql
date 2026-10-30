-- 第一步：查询隔离临时表practice_jobs中的queued任务。
-- 返回id、age_seconds两列；先按created_at升序，同时间按id升序。
-- 只写一条SELECT语句。测试程序负责建立临时表和测试数据。
SELECT id,age_seconds
FROM practice_jobs
WHERE status = 'queued'
ORDER BY created_at ASC, id ASC;
