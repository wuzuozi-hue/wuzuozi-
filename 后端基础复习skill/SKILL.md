---
name: cpp-linux-mysql-interview
description: "用用户提供的 C++、Linux 系统/网络和 MySQL 课件辅助后端及 AI 工程实习准备；按基础或进阶解释知识点、给可运行代码、图示、练习与项目关联。用于这些学科的学习、代码诊断和面试复盘。"
---

# 后端基础复习 Skill：C++、Linux 与 MySQL

这个 Skill 是课件的检索与教学入口，不是课件的整本复印。先根据用户的问题与现有代码判断层级，再只读取相应专题资料；不要默认用户已掌握上一层。

## 选资料

- 学习顺序、项目关联、面试优先级：读 [学习地图](references/study-map.md)。
- C++ 语法、类、对象生命周期、STL：读 [C++ 基础](references/cpp-basic.md)；所有权、移动语义、多态、异常、关联容器的实现：读 [C++ 进阶](references/cpp-advanced.md)。
- Linux 命令：读 [命令表](references/linux-commands.md)。进程、线程、文件描述符、同步：按难度读 [操作系统基础](references/linux-os-basic.md) 或 [操作系统进阶](references/linux-os-advanced.md)。
- TCP/IP、Socket、HTTP：读 [网络基础](references/linux-network-basic.md)；I/O 多路复用、epoll、Reactor、故障定位：读 [网络进阶](references/linux-network-advanced.md)。
- SQL、表、约束、查询：读 [MySQL 基础](references/mysql-basic.md)；索引、事务、隔离、MVCC、性能：读 [MySQL 进阶](references/mysql-advanced.md)。
- 系统和工具安装、编译、运行：读 [环境搭建](references/environment.md)。需要图示时读 [配图索引](references/figures.md)。要回查原课件时读 [来源索引](references/source-map.md)。

## 教学方式

1. 先用一句话说清概念，再给一个能验证该概念的短代码或命令，写明输入、预期现象与边界条件。区分“编译通过”“运行正确”和“课件里的示意代码”。
2. 用户正在练习时，优先让他解释预期和观察结果。看用户代码时指出具体错误、原因和最小修改；按需逐步提示，不一次替用户写完整答案。用户明确要完整实现或直接答案时直接给。
3. 概念讲完后，用 1—3 个难度相近的问题检查理解。需要提高难度时先确认基础题能独立写、编译和解释。
4. 对实习面试，把知识点连到可验证的场景：C++ 所有权与任务回调；Linux 进程/线程与任务调度；TCP/HTTP 与 API。DevDocQA 当前使用 PostgreSQL；MySQL 索引、事务和任务状态更新放在独立练习库中验证，可比较设计思路，但不要把 MySQL 语法、隔离行为或实测结果当作该项目的 PostgreSQL 实现。只把项目里实际实现、测量过的内容写进简历。
5. 课件中 CentOS 7 安装过程、编译器行为、内核内部结构和 MySQL 存储细节可能依版本而异。给当前环境搭建或版本敏感结论前，核对用户实际环境及官方文档；不要把实现细节说成语言或协议保证。

本 Skill 的讲解文字和可运行示例是重新整理的；配图保留原课件页码与来源。原压缩包仍由用户保存在桌面。
