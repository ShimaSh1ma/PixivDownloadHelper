#pragma once

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

class MSocket;
using socketIndex = int;

//客户端套接字
class ClientSocket {
private:
    ClientSocket() = delete;
    ~ClientSocket() = delete;

    //创建socket
    static socketIndex creatSocket(const std::string& _host, const std::string& _port);

    //索引查找socket
    static MSocket* findSocket(socketIndex index);

    //销毁socket
    static void deleteSocket(socketIndex& index);

    //设置socket非阻塞
    static bool setSocketNonblocked(MSocket& _socket);

    //判断socket连接状态
    static bool waitForConnection(MSocket& _socket, int timeout_sec);

    //socket集合
    static std::unordered_map<socketIndex, std::unique_ptr<MSocket>> socketPool;

public:
    //初始化WSA环境
    static void WSAInit();

    //注销WSA环境
    static void WSAClean();

    //初始化ssl环境
    static void sslInit();

    //创建并连接到远程服务器
    static socketIndex connectToServer(const std::string& _host, const std::string& _port);

    //向服务器发送信息
    static bool socketSend(socketIndex& index, const std::string& sendbuf);

    //从服务器接收报文
    static std::string socketReceive(socketIndex& index);

    //断开连接并关闭套接字
    static void disconnectToServer(socketIndex& index);
};
