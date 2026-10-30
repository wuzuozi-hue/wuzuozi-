-- PostgreSQL独立练习：整份文件在同一连接中执行。
-- 只使用临时表；ROLLBACK后练习数据撤销，不修改项目正式jobs表。
BEGIN;

CREATE TEMP TABLE practice_jobs (
    id TEXT PRIMARY KEY,
    status TEXT NOT NULL,
    created_at TIMESTAMP NOT NULL
) ON COMMIT DROP;

-- 模拟启动恢复完成后的数据库状态：
-- J1、J3曾排队；J2曾在执行中，启动时被标记为failed。
INSERT INTO practice_jobs (id, status, created_at) VALUES
    ('J1', 'queued', TIMESTAMP '2026-10-30 12:00:00'),
    ('J2', 'failed', TIMESTAMP '2026-10-30 12:01:00'),
    ('J3', 'queued', TIMESTAMP '2026-10-30 12:05:00');

-- TODO：查询所有queued记录的id、status、created_at。
-- 按created_at从早到晚排序；时间相同再按id升序。
-- 预期依次为J1、J3；J2不属于queued候选。
SELECT id,status,created_at
FROM practice_jobs
WHERE status = 'queued'
ORDER BY created_at ASC, id ASC;
--ASC 表示升序



ROLLBACK;

-- 这是简化的候选查询练习。真实refill还有容量、已加载/待提交ID排除、
-- 超时处理等条件；本练习不等于真实服务已通过重启故障注入。
