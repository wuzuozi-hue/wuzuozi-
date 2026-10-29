-- PostgreSQL独立练习：整份文件在同一连接中执行。
-- 仅创建会话临时表，不修改项目正式表。关闭连接后临时表自动清理。
-- CREATE TEMP TABLE默认在COMMIT后保留数据，便于观察本次练习。
CREATE TEMP TABLE practice_jobs (
    id TEXT PRIMARY KEY,
    status TEXT NOT NULL
);
CREATE TEMP TABLE practice_request_keys (
    idempotency_key TEXT PRIMARY KEY,
    job_id TEXT NOT NULL
);

-- 场景一：两条记录都确认保存。
-- TODO 1：在这里写开启事务的命令。
BEGIN;
INSERT INTO practice_jobs (id, status) VALUES ('J1', 'queued');
INSERT INTO practice_request_keys (idempotency_key, job_id) VALUES ('K1', 'J1');
COMMIT;
-- TODO 2：在这里写提交事务的命令。

SELECT 'after commit' AS stage,
       (SELECT count(*) FROM practice_jobs WHERE id = 'J1') AS job_rows,
       (SELECT count(*) FROM practice_request_keys WHERE idempotency_key = 'K1') AS key_rows;

-- 场景二：两条记录写入后，决定撤销本次事务。
-- TODO 3：在这里写开启事务的命令。
BEGIN;
INSERT INTO practice_jobs (id, status) VALUES ('J2', 'queued');
INSERT INTO practice_request_keys (idempotency_key, job_id) VALUES ('K2', 'J2');
ROLLBACK;
-- TODO 4：在这里写回滚事务的命令。

SELECT 'after rollback' AS stage,
       (SELECT count(*) FROM practice_jobs WHERE id = 'J2') AS job_rows,
       (SELECT count(*) FROM practice_request_keys WHERE idempotency_key = 'K2') AS key_rows;

SELECT 'previous commit remains' AS stage,
       (SELECT count(*) FROM practice_jobs WHERE id = 'J1') AS job_rows,
       (SELECT count(*) FROM practice_request_keys WHERE idempotency_key = 'K1') AS key_rows;

-- 这是显式提交/主动回滚的观察练习；尚未包含故意制造SQL错误的场景。
-- 写完4处TODO后再执行；没有BEGIN时，psql的默认自动提交会改变练习结果。
-- 事务约束数据库里的两条写入，不会自动使数据库提交和内存入队原子完成。
