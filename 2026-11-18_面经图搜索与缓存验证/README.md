# 2026-11-18 实习准备记录

- **面经** · 40 题，覆盖 C++、Linux、网络、数据库、Redis、项目与 AI。[题目、纠错与时间记录](04_板块时间与面经记录.md)
- **项目** · VOD 复盘转码任务入库、通知兜底、租约与 Qt 异步上传。DevDocQA 在隔离环境验证缓存未命中、命中与版本失效。[缓存实验](05_DevDocQA缓存失效实测.md)
- **算法** · 十道题通过各自的文件内用例。二叉搜索树搜索独立通过并完成口述验收，其余题目的提示情况详见当天记录。用 C++17 分别编译练习文件即可执行内置测试。
- **总进度** · 34/100，较前一天增加 1 分，来自二叉搜索树搜索。
- **学习时长** · 按 3 小时 30 分钟计入统计，各板块跨度合计 3 小时 29 分 38 秒。

## 缓存实验复现

将脚本放回 DevDocQA 学习工作区的 `work/devdocqa_cache_check_20261118.py`，从工作区根目录执行：

```powershell
python work/devdocqa_cache_check_20261118.py work/devdocqa_cache_result.json
```

需要该工作区已构建的 DevDocQA 后端、包含 PostgreSQL 和 pgvector 的本地环境及安装了项目 Worker 依赖、httpx、psycopg、redis 和 fakeredis 的 Python 环境。脚本使用临时数据库、测试缓存以及模拟模型。
