-- PostgreSQL练习：只使用本会话临时表，不修改项目的jobs表。
-- 整份文件在同一个数据库连接中执行，结尾ROLLBACK撤销本练习。
BEGIN;

CREATE TEMP TABLE practice_request_keys (
    idempotency_key TEXT PRIMARY KEY,
    job_id TEXT NOT NULL,
    request_content TEXT NOT NULL
) ON COMMIT DROP;

-- 已有的第一次提交：K1对应J1，内容为RAII。
INSERT INTO practice_request_keys (idempotency_key, job_id, request_content)
VALUES ('K1', 'J1', 'RAII');

-- TODO 1：尝试插入('K1', 'J2', 'RAII')。
-- K1冲突时DO NOTHING，并用RETURNING job_id返回本次实际插入的ID。
-- 预期：返回0行；原来的K1/J1记录保留。
-- 在下面编写完整INSERT语句：
INSERT INTO practice_request_keys (idempotency_key, job_id, request_content)
VALUES ('K1','J2','RAII')
ON CONFLICT(idempotency_key) DO NOTHING
RETURNING job_id;
-- TODO 2：查询K1对应的job_id、request_content。
-- 预期：1行，内容为J1、RAII；用于后续判断应复用还是冲突。
-- 在下面编写完整SELECT语句：
SELECT job_id, request_content
FROM practice_request_keys
WHERE idempotency_key = 'K1';


ROLLBACK;

-- 本文件只是幂等键映射的SQL练习，不包含真实任务创建、入队或完整并发验收。
