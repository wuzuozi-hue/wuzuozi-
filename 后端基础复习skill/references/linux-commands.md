# Linux 指令：基础与进阶速查

以 Bash、普通用户权限为默认环境。表中的命令是**示例**，先替换路径、端口和进程名再运行。重点不是背参数，而是能描述“我要观察什么、命令输出说明什么”。来源主要为 L01《Linux 基础指令》、L04《基础开发工具》、L31《网络命令》和 L44《TCP 全连接队列与 tcpdump 抓包》。

## 基础：路径、文件、权限、文本

| 目标 | 命令例子 | 观察与常见错误 |
|---|---|---|
| 确认位置 | `pwd` | 输出当前工作目录；相对路径以此为起点。 |
| 看文件及隐藏项 | `ls -lah` | `-a` 包含点文件，`-l` 看权限/时间，`-h` 易读大小。 |
| 切换目录 | `cd ~/project` | `~` 是当前用户主目录；`cd -` 返回上一个目录。 |
| 确认绝对路径 | `realpath ./README.md` | 文件不存在时会报错或按系统实现处理，先用 `ls` 核对。 |
| 判断类型 | `file ./app`、`stat ./app` | 区分源码、ELF 可执行文件和目录；`stat` 可看权限/时间。 |
| 建立练习目录 | `mkdir -p ~/practice/logs` | `-p` 可创建父目录；不要把测试目录写进项目数据卷。 |
| 复制与改名 | `cp src.txt copy.txt`、`mv copy.txt old.txt` | 覆盖已有文件前先检查目标；`mv` 也用于移动。 |
| 读文件 | `cat config.txt`、`less server.log` | 大日志用 `less`，按 `q` 退出。 |
| 看头尾与跟踪 | `head -n 20 server.log`、`tail -n 50 -f server.log` | `tail -f` 适合看请求时新追加的日志，按 Ctrl+C 停止。 |
| 按名查文件 | `find . -type f -name '*.cpp'` | `.` 是当前目录；文件多时先缩小目录范围。 |
| 按内容查找 | `grep -n 'queue_full' server.log` | `-n` 打印行号；代码库可用 `rg -n 'queue_full' .`（需安装 ripgrep）。 |
| 取文本列 | `awk '{print $1}' access.log` | 按空白分列；实际日志若含空格或 JSON，先确认格式再选字段。 |
| 取行范围 | `sed -n '1,20p' server.log` | 只打印第 1—20 行；`-n` 避免默认再输出全文件。 |
| 计数与去重 | `wc -l server.log`、`sort names.txt \| uniq -c` | `uniq` 只合并相邻重复行，因此常先 `sort`。 |
| 查看归档内容 | `tar -tzf docs.tar.gz` | 先列出文件名和路径，再决定是否解压不明来源的归档。 |
| 看身份与权限 | `id`、`ls -l run.sh` | 先看所有者和权限，再判断为何不能执行。 |
| 增加执行权限 | `chmod u+x ./run.sh` | 只给文件所有者加执行位；不建议为排错直接用 `777`。 |

## 基础：管道、重定向、进程与构建

| 目标 | 命令例子 | 观察与常见错误 |
|---|---|---|
| 管道组合 | `grep 'ERROR' server.log \| tail -n 20` | 左侧标准输出成为右侧标准输入。 |
| 保存标准输出与错误 | `./app >app.out 2>app.err` | `>` 覆盖文件；`2>` 是标准错误。追加使用 `>>`。 |
| 边看边存 | `./app 2>&1 \| tee run.log` | `2>&1` 合并错误输出；`tee` 同时显示并保存。 |
| 环境变量 | `echo "$PATH"`、`export APP_PORT=18880` | `export` 只影响当前 shell 及其子进程。 |
| 查进程 | `ps aux \| grep '[d]evdocqa'`、`pgrep -a devdocqa` | `pgrep` 更适合按进程名查；输出为空不一定是故障，先确认名字。 |
| 请求正常退出 | `kill -TERM 12345` | 将示例数字改成目标 PID；先确认它属于目标进程，`TERM` 给程序清理机会。 |
| 编译 C++17 | `g++ -std=c++17 -Wall -Wextra -g main.cpp -o app` | `-g` 生成调试信息；编译成功后运行 `./app`。 |
| 使用 Makefile | `make`、`make -n` | `make -n` 只显示将执行的命令，适合排查构建规则。 |
| 带调试器运行 | `gdb --args ./app` | 在 gdb 中用 `break main`、`run`、`bt`、`quit`。 |

## 进阶：服务、网络与性能定位

| 目标 | 命令例子 | 观察与常见错误 |
|---|---|---|
| 看地址与路由 | `ip addr`、`ip route` | 区分本机回环地址 `127.0.0.1` 与网卡地址。 |
| 看监听端口 | `ss -ltnp \| grep ':18880'` | `-l` 监听、`-t` TCP、`-n` 不解析名字；进程信息可能需要权限。 |
| 测 HTTP 响应 | `curl -i http://127.0.0.1:18880/health` | 观察状态码、响应头和正文；连接失败先核对端口与服务进程。 |
| 只测连通性 | `ping -c 3 127.0.0.1` | ICMP 连通不等于 HTTP 服务可用。 |
| 查域名解析 | `getent hosts example.com` | DNS 结果可能变化；有 `dig` 时可用 `dig example.com`。 |
| 查打开的文件 | `lsof -p 12345` | 将示例数字改成目标 PID；可看日志、socket 和文件描述符，工具可能需要单独安装。 |
| 查服务状态 | `systemctl status myservice`、`journalctl -u myservice -n 50` | 适用于启用 systemd 的系统；WSL 或容器中未必提供此服务管理方式。 |
| 观察系统调用 | `strace -f -e trace=network ./app` | 用于查看网络相关调用；输出可能很多，先限制范围。 |
| 抓 TCP 报文 | `sudo tcpdump -i any -nn 'tcp port 18880'` | 仅在自己的测试环境抓包；观察 SYN/ACK 与重传。 |
| 看资源占用 | `top`、`free -h`、`df -h` | 分别看进程 CPU/内存、系统内存、文件系统空间。 |

### 小实验：排查“服务访问不了”

按顺序执行并记录结果；不要只写“接口失败”：

```bash
# 1. 进程是否还在？
pgrep -a devdocqa

# 2. 预期端口是否真的监听？
ss -ltnp | grep ':18880'

# 3. HTTP 到了服务后返回什么？
curl -i --max-time 5 http://127.0.0.1:18880/health

# 4. 最近有没有报错？路径按项目实际位置修改。
tail -n 50 ./logs/server.log
```

若第 1 步为空，查启动失败；第 1 步有进程而第 2 步为空，查绑定地址/端口；第 2 步有监听而第 3 步失败，查防火墙、代理或协议；第 3 步有明确 `4xx/5xx`，再沿请求日志与依赖状态排查。
