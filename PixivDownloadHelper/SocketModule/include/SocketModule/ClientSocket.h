#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class MSocket;
class HttpResponseParser;

using socketIndex = int;

// 初始化WSA环境
void WSAInit();
// 注销WSA环境
void WSAClean();
// 初始化ssl环境
void sslInit();

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

    // 重用socket tcp链接
    static socketIndex reuseSocket(const std::string& _host);

    // socket集合
    static std::unordered_map<socketIndex, std::unique_ptr<MSocket>> socketPool;

  public:
    // 创建并连接到远程服务器
    static socketIndex connectToServer(const std::string& _host, const std::string& _port);

    // 向服务器发送信息
    static bool socketSend(socketIndex& index, const std::string& sendbuf);

    // 从服务器接收报文
    static std::unique_ptr<HttpResponseParser> socketReceive(socketIndex& index);

    // 释放对当前socket的控制，而不断开链接，复用socket
    static void releaseSocket(socketIndex& index);

    // 断开连接并关闭套接字
    static void disconnectToServer(socketIndex& index);
};
