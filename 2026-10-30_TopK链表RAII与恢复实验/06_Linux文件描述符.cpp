#include <cstdio>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

// Linux练习：在本文件所在目录运行，读取同目录的06_fd示例.txt。
// 当前本机WSL不可用，先阅读并完成代码；在Linux环境就绪后再编译运行。
int main() {
    // O_RDONLY：只读打开。成功时fd是非负整数；失败返回-1。
    int fd = ::open("06_fd示例.txt", O_RDONLY);
    if (fd < 0) {
        std::perror("open");
        return 1;
    }

    char buffer[64];
    // read返回实际读到的字节数；0表示到达文件末尾；-1表示出错。
    ssize_t bytes = ::read(fd, buffer, sizeof(buffer));
    if (bytes < 0) {
        std::perror("read");
        ::close(fd); // 出错时释放已经打开的描述符。
        return 1;
    }

    std::cout << "read bytes: " << bytes << '\n';
    std::cout.write(buffer, bytes);

    // TODO：正常读取结束后，也要释放fd；在这里补一条close调用。
    close(fd);
    return 0;
}
