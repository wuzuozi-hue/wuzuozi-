# 2026 年 11 月 17 日 · VOD 任务租约重领

测试窗口于北京时间 20:09:44 启动，20:10:46 写入结束结果。这段时间包含 SSH 认证等待。

## 实测结果

远端 `/home/dev/workspace/vod-platform` 使用现有 CTest 的临时 MariaDB 数据库。测试通过直接调整临时库中的 `lease_until` 制造过期，实际写回调用项目的 `JobStore`。

| 操作 | 数据库结果 |
|---|---|
| A 认领，租约过期后 B 重新认领 | `video_id` 相同，`claim_id` 更新，`attempts = 2` |
| A 迟到调用 `fail()` | 任务状态、认领标识、租约和视频记录均保持原值 |
| A 迟到调用 `complete()` | 返回 `false`，上述记录保持原值 |
| B 调用 `complete()` | 返回 `true`，任务变为完成，视频进入待审核，`completed_claim_id` 记录 B 的认领标识 |

终端记录 `lease reclaim PASS`，整个集成流程退出码为 `0`。用例验收条件是 **B 已经重新认领**。个人口述验收待完成。

## 复现

将相邻的 C++ 测试和 Python 运行器放在同一目录。在已经配置 `vod_session_mysql_integration` 的 VOD 项目目录启动运行器。

```sh
python3 /path/to/14_VOD_运行租约重领测试.py build
```
