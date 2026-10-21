-- 2026-10-21 独立复测：条件更新、事务、重启恢复
-- 在本文件填写答案；旧练习文件不用改。
-- 这是推演题，尚未在 PostgreSQL 中执行。

-- 题 1：数据库中 J7 的状态为 queued。
-- 写一条 PostgreSQL UPDATE：只有 J7 仍为 queued 时，才将它改为 running，
-- 并返回成功认领的任务 ID。
UPDATE practice_jobs
SET status = 'running'
WHERE id = 'J7' AND status = 'queued'
RETURNING id;

-- 两个 worker 先后执行这条语句。第一个成功并提交后：
-- 第一个 RETURNING 返回几行？
-- 第二个 RETURNING 返回几行？
1.1
2.0


-- 题 2：同一事务内先插入任务 J8，再插入幂等键 K8 -> J8。
-- 如果第二次插入失败，事务回滚后数据库还剩下哪条新记录？
-- 答：K8

-- 题 3：服务崩溃前有三个对象：
-- J9：queued 的问题任务；J10：running 的问题任务；
-- D11：processing 的文档，已有部分片段。

-- 按 DevDocQA 当前单实例恢复策略填写：
-- J9 重启后的数据库状态，以及会不会重新入队：queued 会
-- J10 重启后的数据库状态，以及 error：failed restarted
-- D11 重启后的状态，以及未完成片段是否保留： failed 不保留
