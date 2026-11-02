-- PostgreSQL 临时表实验，不修改项目表。
-- J1 和 key-1 作为实验初始数据，在事务外建立。
CREATE TEMP TABLE practice_jobs_tx (
    id text PRIMARY KEY
);
CREATE TEMP TABLE practice_keys_tx (
    request_key text PRIMARY KEY,
    job_id text NOT NULL REFERENCES practice_jobs_tx(id)
);
INSERT INTO practice_jobs_tx(id) VALUES ('J1');
INSERT INTO practice_keys_tx(request_key, job_id) VALUES ('key-1', 'J1');

BEGIN;
-- TODO 1：向 practice_jobs_tx 插入任务 J2。
INSERT INTO practice_jobs_tx(id) VALUES ('J2');
INSERT INTO practice_keys_tx(request_key, job_id) VALUES ('key-1', 'J2');

-- TODO 2：向 practice_keys_tx 插入映射 key-1 -> J2。
-- 不使用 ON CONFLICT，本次故意触发唯一键冲突。

-- 冲突后回滚事务，撤销本次 J2 写入。
ROLLBACK;

-- 检查：预期只剩最初的 J1 和 key-1 -> J1。
SELECT id FROM practice_jobs_tx ORDER BY id;
SELECT request_key, job_id FROM practice_keys_tx ORDER BY request_key;
