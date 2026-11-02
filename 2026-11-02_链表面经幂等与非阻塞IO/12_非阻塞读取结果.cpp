#include <iostream>

// TCP 流、非零长度读取的教学模型；不执行真实系统调用。
enum class ErrorKind { None, Again, Interrupted, Other };
enum class NextAction { ProcessData, PeerClosed, WaitReadable, Retry, Error };

NextAction decideRead(int bytes, ErrorKind error) {
    // bytes > 0：读取到数据，返回 ProcessData。
    if(bytes > 0){
        return NextAction::ProcessData;
    }
    if(bytes == 0){
        return NextAction::PeerClosed;
    }
    if(bytes == -1&& error == ErrorKind::Again){
        return NextAction::WaitReadable;
    }
    if(bytes == -1 && error == ErrorKind::Interrupted){
        return NextAction::Retry;
    }
    // bytes == 0：对端正常关闭发送方向，返回 PeerClosed。
    // bytes == -1 且 error 是 Again：暂时没有数据，返回 WaitReadable。
    // bytes == -1 且 error 是 Interrupted：被信号中断，返回 Retry。
    // 其他错误：返回 Error。
    return NextAction::Error;
}

void check(const char* name, bool ok) {
    std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("data", decideRead(12, ErrorKind::None) == NextAction::ProcessData);
    check("peer closed", decideRead(0, ErrorKind::None) == NextAction::PeerClosed);
    check("not ready", decideRead(-1, ErrorKind::Again) == NextAction::WaitReadable);
    check("interrupted", decideRead(-1, ErrorKind::Interrupted) == NextAction::Retry);
    check("other error", decideRead(-1, ErrorKind::Other) == NextAction::Error);
}
