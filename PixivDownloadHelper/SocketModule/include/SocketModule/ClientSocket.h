#pragma once

#include <vector>
#include <string>

class MSocket;

//客户端套接字
class ClientSocketPool {
private:
    ClientSocketPool() = delete;
    ~ClientSocketPool() = delete;

    //创建socket
    static MSocket* creatSocket() noexcept;

    //销毁socket
    static void deleteSocket(MSocket& _socket) noexcept;

#ifdef _WIN32
    //WSADATA对象，用于向winsock注册本应用
    static WSADATA wsaData;
#endif

public:
    //初始化WSA环境
    static void WSAInit();

    //注销WSA环境
    static void WSAClean();

    //初始化ssl环境
    static void sslInit();

    //创建并连接到远程服务器
    static void sslConnectToServer(MSocket& _socket);

    //向服务器发送信息
    static void socketSend(MSocket& _socket, const std::string& sendbuf);

    //从服务器接收报文
    static std::string socketReceive(MSocket& _socket);

    //断开连接并关闭套接字
    static void sslDisconnectToServer(MSocket& _socket);
};
