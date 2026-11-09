-- PostgreSQL 独立练习：任务创建与幂等映射放在同一个事务中
-- 只使用下面的练习表，不修改项目现有的 jobs 或 documents 表。
-- 每次重新练习前可先在练习数据库清理本文件创建的两张表。

CREATE TABLE IF NOT EXISTS study_idem_jobs (
    id TEXT PRIMARY KEY,
    status TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS study_idem_requests (
    request_key TEXT PRIMARY KEY,
    request_hash TEXT NOT NULL,
    job_id TEXT NOT NULL REFERENCES study_idem_jobs(id)
);
BEGIN;

INSERT INTO study_idem_jobs (id,status)
VALUES ('J1','queued');

INSERT INTO study_idem_requests(request_key,request_hash,job_id)
VALUES ('key-1', 'hash-A', 'J1');

COMMIT;

-- 情景一：写一个事务，创建 J1（queued），并记录
-- key-1 / hash-A / J1。两条都成功后提交。

BEGIN;

INSERT INTO study_idem_jobs (id,status)
VALUES ('J2','queued');

INSERT INTO study_idem_requests(request_key,request_hash,job_id)
VALUES ('key-1', 'hash-A', 'J2');

ROLLBACK;
-- 情景二：再写一个事务，创建 J2（queued），尝试记录
-- key-1 / hash-A / J2。request_key 已存在，会发生唯一约束冲突。
-- 需要回滚此事务。执行时报错是这个练习的预期现象。


-- 查询结果：成功后应只保留 J1 及 key-1 -> J1；J2 不应留下。
SELECT * FROM study_idem_jobs ORDER BY id;
SELECT * FROM study_idem_requests ORDER BY request_key;
