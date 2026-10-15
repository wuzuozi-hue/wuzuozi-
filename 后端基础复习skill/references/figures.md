# 精选配图

这些图片从用户提供的课件页直接渲染，保留原页文字与水印。学习时先读对应专题的解释，再用图验证数据流或结构；图中的具体内核实现、编译器布局和版本示例不能当作跨版本保证。原件名称见 [来源索引](source-map.md)。

## C++

- [虚函数调用示意](../assets/figures/cpp-virtual-dispatch_C14_p11.png)：基类指针指向不同派生对象时调用不同覆盖函数。来源 C14 第 11 页；用于 C++ 进阶的动态绑定。图中的 `vptr` 布局是常见实现，不是标准规定的唯一对象布局。
- [红黑树变色与局部结构](../assets/figures/cpp-red-black-recolor_C18_p6.png)：理解平衡树维护不变量的一个具体场景。来源 C18 第 6 页；用于关联容器底层结构，不要求初学阶段背所有旋转分支。

## Linux 操作系统与网络

- [进程状态转换](../assets/figures/linux-process-states_L05_p11.png)：区分就绪、运行、阻塞与终止。来源 L05 第 11 页；图是教学抽象，具体 Linux 状态以当前内核和 `ps` 输出为准。
- [OSI 分层上半页](../assets/figures/network-osi-upper_L21_p7.png) 与 [下半页](../assets/figures/network-osi-lower_L21_p8.png)：把应用、传输、网络、链路的职责放到不同层。来源 L21 第 7—8 页；讲工程中的 TCP/IP 时注意层数是模型选择。
- [I/O 模型的等待与拷贝](../assets/figures/linux-io-models_L25_p3.png)：比较同步多路复用和异步 I/O 的时序。来源 L25 第 3 页；用于解释“事件循环不能阻塞在模型调用”。
- [epoll 教学结构图](../assets/figures/network-epoll-structure_L28_p6.png)：展示注册对象和就绪事件的关系。来源 L28 第 6 页；红黑树、链表细节是课件所示实现，不保证所有内核版本一致。
- [TCP 连接、数据与关闭时序](../assets/figures/network-tcp-lifecycle_L43_p6.png)：将 `socket/bind/listen/accept/connect/close` 与 TCP 状态对应。来源 L43 第 6 页。

## MySQL

- [B+ 树页与叶子链](../assets/figures/mysql-bplus-pages_M11_p11.png)：理解主键索引与范围扫描。来源 M11 第 11 页；图是简化结构。
- [B 树与 B+ 树对比](../assets/figures/mysql-b-vs-bplus_M11_p12.png)：比较数据放置位置与叶子链接。来源 M11 第 12 页；用于理解为什么 InnoDB 的常见索引适合范围查询。
- [MVCC 历史版本链](../assets/figures/mysql-mvcc-version-chain_M12_p22.png)：通过当前记录与 undo 历史版本理解快照读。来源 M12 第 22 页；可见性还取决于 Read View，不能只看版本链。

需要在回答中展示某张图时，使用其绝对文件路径或支持本地图片的 Markdown 引用，并在图下写明“来源 ID＋页码”和一句该图说明的问题。
