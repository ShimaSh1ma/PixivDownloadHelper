#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class MSocket;
class HttpResponseParser;

using socketIndex = int;

enum class selectType {
    READ,
    WRITE,
    READ_AND_WRITE
};

constexpr const size_t timeWaitSeconds = 5;

// 客户端套接字
class ClientSocket {
  private:
    ClientSocket() = delete;
    ~ClientSocket() = delete;

    // 创建socket
    static socketIndex creatSocket(const std::string& _host, const std::string& _port);

    // 索引查找socket
    static MSocket* findSocket(socketIndex& index);

    // 销毁socket
    static void deleteSocket(socketIndex& index);

    // 设置socket非阻塞
    static bool setSocketNonblocked(MSocket& _socket);

    // 判断socket连接状态
    static bool waitForConnection(MSocket& _socket, int timeout_sec);

    // 使用select检查套接字是否可用
    static bool selectSocket(const MSocket& _socket, selectType type = selectType::READ_AND_WRITE,
                             int timeoutSecond = timeWaitSeconds);

    // socket集合
    static std::unordered_map<socketIndex, std::unique_ptr<MSocket>> socketPool;

  public:
    // 初始化WSA环境
    static void WSAInit();

    // 注销WSA环境
    static void WSAClean();

    // 初始化ssl环境
    static void sslInit();

    // 创建并连接到远程服务器
    static socketIndex connectToServer(const std::string& _host, const std::string& _port);

    // 向服务器发送信息
    static bool socketSend(socketIndex& index, const std::string& sendbuf);

    // 从服务器接收报文
    static std::unique_ptr<HttpResponseParser> socketReceive(socketIndex& index);

    // 断开连接并关闭套接字
    static void disconnectToServer(socketIndex& index);
};
