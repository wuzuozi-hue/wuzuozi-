# MySQL 进阶：索引、事务、MVCC 与慢查询

前置：能在 [MySQL 基础](mysql-basic.md) 的专用练习库里建表、写连接查询，并解释事务提交/回滚；也可先做[连接与子查询练习](mysql-practice.md)。DevDocQA 当前项目使用 PostgreSQL，本页的 MySQL 代码是独立训练。来源：M11 索引、M12 事务、M13 视图、M14 用户管理、M15 C 语言连接示例。图见 [B+ 树页](../assets/figures/mysql-bplus-pages_M11_p11.png)、[B 树与 B+ 树比较](../assets/figures/mysql-b-vs-bplus_M11_p12.png)、[MVCC 版本链](../assets/figures/mysql-mvcc-version-chain_M12_p22.png)。

## 1. 索引是有代价的查找结构

InnoDB 的常见 B+ 树索引按键排序；主键聚簇索引的叶页与完整行相关，二级索引叶页包含索引键和主键，按二级索引查到主键后可能还需回表。B+ 树的有序性有利于范围查找，但索引会增加写入、维护和存储成本。不是“给每个 WHERE 字段都加索引”就更快。

```sql
USE intern_lab;
EXPLAIN
SELECT id, created_at
FROM jobs
WHERE state = 'queued'
ORDER BY created_at, id
LIMIT 20;

-- 只在第一次练习时执行，重复创建同名索引会报错。
CREATE INDEX idx_jobs_state_created_id ON jobs(state, created_at, id);

-- 保持查询文本不变，比较创建索引前后的计划。
EXPLAIN
SELECT id, created_at
FROM jobs
WHERE state = 'queued'
ORDER BY created_at, id
LIMIT 20;
```

这个联合索引把筛选列放前面，再接排序列；是否被优化器采用，需要看真实数据分布与 `EXPLAIN` 的 `key`、`rows`、`Extra` 等信息。`rows` 是优化器估计的扫描行数，不是实际计数，参见 [MySQL 官方 EXPLAIN 字段说明](https://dev.mysql.com/doc/refman/8.0/en/explain-output.html)。联合索引可利用的前缀和范围条件受查询形式影响，不能机械记成“第二列永远不能用”。如果查询字段都在索引里，可减少回表；仍需看优化器选择。InnoDB 二级索引还隐含主键列，因此示例最后显式列出的 `id` 可以作为进一步讨论索引冗余与排序行为的题目，不能不看 [索引扩展规则](https://dev.mysql.com/doc/refman/8.0/en/index-extensions.html) 就断定它必需。

练习：先记录索引前后的 `EXPLAIN`，生成足够的测试数据，再比较查询时间与写入成本。小表即使没走索引也可能更快；不能把一次微小样本的耗时写成性能优化成果。

## 2. 隔离级别、当前读与快照读

读未提交、读已提交、可重复读、串行化是常见隔离级别。先用 `SELECT @@transaction_isolation;` 查看当前会话，别假设所有环境默认相同。InnoDB 的普通一致性读通常使用 MVCC 快照；`SELECT ... FOR UPDATE` 是加锁读取当前可见数据。读已提交与可重复读在 Read View 创建/复用时机上的差别，会影响同一事务两次读取的结果（M12）。

[版本链图](../assets/figures/mysql-mvcc-version-chain_M12_p22.png) 展示当前记录沿 undo 历史版本回溯；**能否看到某个版本**还需要 Read View 的可见性规则。MVCC 主要解决读写并发的一部分问题，不代表所有查询都不加锁，也不能独自防止所有写写冲突。

```sql
-- 在两个独立 MySQL 会话中对同一练习表实验；先记录当前隔离级别。
SELECT @@transaction_isolation;
START TRANSACTION;
SELECT id, state FROM jobs WHERE id = 1;
-- 让另一会话修改并提交 id=1 的状态，再执行下一句观察。
SELECT id, state FROM jobs WHERE id = 1;
COMMIT;
```

实验前需清楚隔离级别、第一条读取何时发生和另一会话是否真的提交；否则两次结果不同不能证明某个理论结论。

## 3. 并发任务的状态转换

任务认领需要避免两个工作者都把同一排队任务当成自己的。一个简单的单任务状态转换是条件更新：

```sql
UPDATE jobs
SET state = 'running'
WHERE id = 1 AND state = 'queued';
SELECT ROW_COUNT() AS claimed; -- 紧接上条 UPDATE，并在同一连接执行
```

`claimed = 1` 表示本次成功转换一行；`0` 表示任务不存在或已不在排队状态。真实调度还要处理事务边界、工作者崩溃、过期任务恢复，以及重复请求的幂等性。若使用 `SELECT ... FOR UPDATE SKIP LOCKED` 之类语法，先核对当前 MySQL 版本及其锁语义。

## 4. 排查慢查询与故障

1. 先保存原 SQL、参数、表行数与慢查询耗时，再看 `EXPLAIN`，观察实际是否走期望索引。
2. 区分扫描慢、回表多、排序/临时表、锁等待和网络慢；一个查询耗时长不一定是索引问题。
3. 修改索引或 SQL 后用同一数据集、并发和缓存条件复测，记录收益及写入/空间代价。
4. 死锁或锁等待超时要捕获数据库错误，并在操作具备幂等性时有界重试；别把失败静默改成“成功”。

视图便于封装查询，但不替代权限和索引设计（M13）。应用连接应使用权限受限的账号、参数化查询和明确的连接生命周期；M14—M15 的课件示例需按所用驱动与版本重新验证，不能在仓库里硬编码密码。

面试自测：联合索引 `(state, created_at, id)` 对哪类查询有帮助？MVCC 版本链与 Read View 各负责什么？为什么普通 `SELECT` 与 `SELECT ... FOR UPDATE` 结果/锁行为可能不同？
