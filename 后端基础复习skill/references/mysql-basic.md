# MySQL 基础：表、约束、查询与事务入门

目标：在**专用练习数据库**里建表、插入、筛选、聚合、连接两张表，并用事务完成一次状态变更。DevDocQA 当前项目使用 PostgreSQL；本页是独立的 MySQL 练习，不表示项目已经迁移到 MySQL。来源：M02—M10；安装单列在 [环境搭建](environment.md)，不要直接照抄 M01 的 CentOS 7 步骤到 WSL Ubuntu。

## 1. 先理解数据库、表和类型

数据库存放相关表，表由行和列组成；MySQL 客户端发送 SQL，服务端执行并持久化数据。`INT/BIGINT` 存整数，`VARCHAR(n)` 存有限长度文本，`TEXT` 存更长文本，时间可用 `DATETIME`/`TIMESTAMP`；金额等精确十进制值用 `DECIMAL`，不要用浮点数做精确金额。`NULL` 表示未知/缺失，与空字符串和 0 不同（M02—M05）。

## 2. 表结构和约束

先按[环境搭建](environment.md)创建 `intern_lab`，以下在这个**专用练习库**运行，**不要在已有项目库上直接执行**。练习账号只需拥有 `intern_lab` 上的权限，无须拥有创建数据库的权限。外键保证任务引用真实文档；`UNIQUE` 只按定义的列限制重复；索引选择留到进阶。

```sql
USE intern_lab;

CREATE TABLE IF NOT EXISTS documents (
    id BIGINT PRIMARY KEY AUTO_INCREMENT,
    title VARCHAR(200) NOT NULL,
    state VARCHAR(20) NOT NULL,
    created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS jobs (
    id BIGINT PRIMARY KEY AUTO_INCREMENT,
    document_id BIGINT NOT NULL,
    state VARCHAR(20) NOT NULL,
    created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT fk_jobs_document FOREIGN KEY (document_id) REFERENCES documents(id)
) ENGINE=InnoDB;
```

`PRIMARY KEY` 唯一且非空；`NOT NULL` 禁止缺失值；外键约束跨表引用（M06）。生产系统还要设计文档删除策略、状态枚举、迁移与审计；此例只为学习。一个文档可以对应多条任务，所以 `jobs.document_id` 不加唯一约束。

## 3. CRUD、条件、聚合、连接

```sql
INSERT INTO documents (title, state) VALUES ('RAII.md', 'ready');
INSERT INTO documents (title, state) VALUES ('TCP.md', 'processing');

SELECT id, title, state FROM documents
WHERE state = 'ready' ORDER BY id DESC LIMIT 10;

INSERT INTO jobs (document_id, state)
SELECT id, 'queued' FROM documents WHERE title = 'RAII.md' ORDER BY id DESC LIMIT 1;

SELECT d.id, d.title, COUNT(j.id) AS job_count
FROM documents AS d
LEFT JOIN jobs AS j ON j.document_id = d.id
GROUP BY d.id, d.title
ORDER BY d.id;
```

`WHERE` 过滤行；`ORDER BY` 明确排序；`LIMIT` 截取结果；`COUNT(j.id)` 不计入 `LEFT JOIN` 产生的空右表行，而 `COUNT(*)` 会计入。左连接保留没有任务的文档；内连接只保留匹配的行（M07—M10）。写 `UPDATE`/`DELETE` 前先用同样的 `WHERE` 做 `SELECT` 核对影响范围。

## 4. 事务入门

一组相关写入应作为一个事务处理：成功则 `COMMIT`，失败则 `ROLLBACK`。下面先锁定一个排队任务，避免两个工作者同时认领；这是 MySQL/InnoDB 的教学示例，仍须检查实际影响行数。

```sql
START TRANSACTION;
SELECT id, state FROM jobs WHERE id = 1 FOR UPDATE;
UPDATE jobs SET state = 'running' WHERE id = 1 AND state = 'queued';
SELECT ROW_COUNT() AS claimed;
-- 在交互式客户端检查 claimed；为 1 时手动执行 COMMIT，
-- 为 0 或出错时手动执行 ROLLBACK。不要把两条结束语句一起运行。
```

事务的原子性不意味着外部模型调用也能被数据库回滚。服务端通常先持久化任务状态，再在事务外调用耗时模型，并为失败、超时和重启定义状态转换。隔离级别、锁与 MVCC 见 [MySQL 进阶](mysql-advanced.md)。若多次练习，先查询 `jobs` 中仍为 `queued` 的任务 ID，再替换示例中的 `id = 1`；不要把示例数字当成总会存在的任务。

接着做[独立 SQL 练习](mysql-practice.md)：它提供少量员工／部门数据和逐步提示，用于连接、聚合及子查询；数据与 DevDocQA 项目库无关。

面试自测：`NULL` 与 `''` 的差别？`LEFT JOIN` 和 `INNER JOIN` 的差别？为什么 `COUNT(j.id)` 与 `COUNT(*)` 在左连接后可能不同？事务能回滚已经发出的 HTTP 请求吗？
