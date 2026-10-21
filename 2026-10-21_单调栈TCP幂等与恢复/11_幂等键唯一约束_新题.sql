-- 2026-10-21 新题：幂等键的作用范围
-- 只做设计练习，不是 DevDocQA 已实现的数据库迁移。

-- client_id 是调用方身份，不是明文 API Key。
-- idempotency_key 是客户端为一次请求生成的标识。
-- request_hash 用于判断同一个键对应的请求内容是否一致。
-- job_id 指向已经创建的任务。

CREATE TABLE practice_request_keys (
    client_id text NOT NULL,
    idempotency_key text NOT NULL,
    request_hash text NOT NULL,
    job_id text NOT NULL,
    UNIQUE (client_id,idempotency_key)
);

-- 场景：A 使用 K7 创建 J1；B 也使用 K7 创建 J2。
-- 问 1：A 和 B 是不同调用方，这两条记录应该允许同时存在吗？
-- 答：可以存在

-- 问 2：A 再次使用 K7，但请求内容与 J1 不同，应返回旧 J1 还是拒绝？
-- 答：拒绝
