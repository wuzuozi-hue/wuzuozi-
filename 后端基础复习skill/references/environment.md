# 环境搭建：Windows + WSL2 Ubuntu、C++、MySQL

本页只负责搭建**学习环境**。课件中的 CentOS 7、旧版软件安装步骤适合了解原理，不应直接照搬到当前 Windows + WSL2。先检查现有环境；已经可用的组件无需重装。版本和安装入口以 [微软 WSL 文档](https://learn.microsoft.com/windows/wsl/install)、[WSL 开发环境文档](https://learn.microsoft.com/windows/wsl/setup/environment)、[Ubuntu 包信息](https://packages.ubuntu.com/search?keywords=build-essential)、[MySQL 官方文档](https://dev.mysql.com/doc/refman/8.0/en/linux-installation.html)为准。原课件对应 L04（开发工具）和 M01（MySQL 安装）。

## 1. 先确认所在终端

在 **PowerShell** 中执行：

```powershell
wsl --status
wsl --list --verbose
```

若 WSL 尚未安装，按微软当前文档在管理员 PowerShell 执行 `wsl --install`，完成安装和可能的重启后再继续。若已有 Ubuntu，运行 `wsl` 进入 Linux。下文 `$` 开头的命令均在 **Ubuntu Bash** 中执行，不是在 PowerShell 中执行。

```bash
uname -a
cat /etc/os-release
pwd
```

预期：能看到 Linux 内核信息、Ubuntu 版本和当前目录。版本号以实际输出为准。

## 2. C++ 编译、调试与 CMake

在 Ubuntu Bash 中安装常用工具：

```bash
sudo apt update
sudo apt install build-essential cmake gdb git curl pkg-config
g++ --version
cmake --version
gdb --version
```

在个人练习目录验证**编译和运行是两步**：

```bash
mkdir -p ~/cpp-lab
cd ~/cpp-lab
cat > hello.cpp <<'EOF'
#include <iostream>
int main() { std::cout << "hello C++17\n"; }
EOF
g++ -std=c++17 -Wall -Wextra -g hello.cpp -o hello
./hello
```

预期输出 `hello C++17`。只有编译器版本号并不足以证明示例能运行。

最小 CMake 工程可用以下文件验证；把 `hello.cpp` 放在同一目录：

```cmake
cmake_minimum_required(VERSION 3.16)
project(cpp_lab LANGUAGES CXX)
add_executable(hello hello.cpp)
target_compile_features(hello PRIVATE cxx_std_17)
```

将以上内容保存为 `CMakeLists.txt`，然后运行：

```bash
cmake -S . -B build
cmake --build build
./build/hello
```

在 VS Code 中用 **WSL 窗口**打开 WSL 项目目录（Ubuntu 终端中 `code .`，如命令未安装，按 [微软 WSL 开发环境说明](https://learn.microsoft.com/windows/wsl/setup/environment)配置）。确认左下角显示 WSL、集成终端能运行 `g++ --version`，再使用 F5。若出现 `compilerPath=gcc`、找不到编译器或 F5 只显示启动信息，先在**同一个环境**的终端执行上面的编译与运行，再核对 VS Code 的编译器路径和调试配置；不要混用 Windows `cl.exe`、MinGW、WSL 的头文件和调试器。

## 3. MySQL：先选一个隔离的练习实例

已有项目若用 PostgreSQL，不需要为了学习 MySQL 改动项目数据库。MySQL 练习放在独立实例与 `intern_lab` 库中。Ubuntu 本地安装的一种方式：

```bash
sudo apt update
sudo apt install mysql-server
sudo service mysql start
sudo service mysql status
sudo mysql -e "SELECT VERSION();"
```

Ubuntu/WSL 的服务管理方式会随发行版和 systemd 配置变化；`service` 不可用时先查看 `ps -ef | grep '[m]ysqld'` 和本机文档，不要反复安装另一套 MySQL。创建专用练习库与用户；把下面的 `CHANGE_ME_LOCAL_PASSWORD` 换成自己设置的密码，**不要提交到 Git**：

```sql
CREATE DATABASE IF NOT EXISTS intern_lab CHARACTER SET utf8mb4;
CREATE USER IF NOT EXISTS 'intern_lab'@'localhost' IDENTIFIED BY 'CHANGE_ME_LOCAL_PASSWORD';
GRANT ALL PRIVILEGES ON intern_lab.* TO 'intern_lab'@'localhost';
```

在 `sudo mysql` 交互界面执行上面的 SQL，再测试 `mysql -u intern_lab -p intern_lab`；`-p` 后不直接拼密码，由终端提示输入。这个用户只用于本地练习库，不给全局管理权限。执行 `SELECT VERSION();`、`SHOW DATABASES;` 验证连接。用完退出输入 `exit`。

`CREATE USER IF NOT EXISTS` 遇到已有同名用户时不会重设其密码；如果登录失败，先确认是否用了旧密码，再决定是否在本地练习实例中执行 `ALTER USER`，不要直接修改项目数据库的用户。

## 4. 练习时的最小排错顺序

| 现象 | 先查什么 | 下一步 |
|---|---|---|
| `g++: command not found` | `command -v g++`、`cat /etc/os-release` | 确认正在 Ubuntu Bash 且 `build-essential` 安装成功。 |
| 编译成功但无法执行 | `pwd`、`ls -l ./hello` | 核对运行的是 `./hello`，不是仅输入文件名。 |
| VS Code F5 没输出 | 集成终端是否能运行二进制 | 核对 VS Code 所在环境、启动配置和输出位置。 |
| MySQL 连接失败 | `sudo service mysql status`、`ss -ltn` | 区分服务没启动、密码/用户错误和端口问题。 |
| MySQL SQL 报错 | `SELECT VERSION();`、当前库 `SELECT DATABASE();` | 核对版本、数据库名、表结构和错误原文。 |

每次记录**命令、输出、预期与实际差异**，后续才能独立复现和定位。
