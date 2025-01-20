#pragma once

#include <openssl/err.h>
#include <openssl/ssl.h>

#include <atomic>
#include <string>

// windows头文件
#if defined(_WIN32)

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "libssl.lib")
#pragma comment(lib, "libcrypto.lib")
#pragma comment(lib, "Ws2_32.lib")

#endif

// mac/linux头文件
#if defined(__linux__) || defined(__APPLE__)

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

using SOCKET = int;
constexpr const int INVALID_SOCKET = -1;
constexpr const int SOCKET_ERROR = -1;

#define SD_SEND SHUT_WR
#define SD_RECEIVE SHUT_RD
#define SD_BOTH SHUT_RDWR

#define closesocket close

#define WSAGetLastError() (errno)

#endif

class MSocket final {
  public:
    MSocket(const char* _host, const char* _port);
    ~MSocket();

    MSocket(const MSocket&) = delete;
    MSocket& operator=(const MSocket&) = delete;
    MSocket(MSocket&&) = delete;
    MSocket& operator=(MSocket&&) = delete;

    void setHostAndPort(const char* _host, const char* _port) noexcept;
    const std::string getHost();

    // 标志socket是否繁忙
    std::atomic_bool isBusy = true;

  private:
    // 关闭socket并清理资源
    void socketClose();

    // socket对象
    SOCKET socket = INVALID_SOCKET;

    // sslsocket对象
    SSL* sslSocket = nullptr;

    // 目标主机名
    std::string host;
    // 目标端口号
    std::string port;

    // 存储ip地址类型及协议相关信息
    struct addrinfo ipAddr;
    // 存放DNS请求后的ip地址信息
    struct addrinfo* ipResult = nullptr;

    // 选择SSL版本
    const SSL_METHOD* meth = SSLv23_client_method();
    // 声明SSL上下文
    SSL_CTX* ctx = nullptr;

    // 函数返回结果
    int result;
    // 错误信息
    std::string errorLog;

    // ClientSocket静态类控制socket
    friend class ClientSocket;
};