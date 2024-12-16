#pragma once

#include <openssl/ssl.h>
#include <openssl/err.h>

#if defined(_WIN32)

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib,"libssl.lib")
#pragma comment(lib,"libcrypto.lib")
#pragma comment(lib,"Ws2_32.lib")

#endif

#if defined(__linux__ )|| defined(__APPLE__)

#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

using SOCKET = int;
constexpr const int INVALID_SOCKET = -1;
constexpr const int SOCKET_ERROR = -1;

#define SD_SEND SHUT_WR
#define SD_RECEIVE SHUT_RD
#define SD_BOTH SHUT_RDWR

#define closesocket close

#define WSAGetLastError() (errno)

#endif 

#include <vector>
#include <string>

#include "DataProcess.h"
#include "SocketConstant.h"

class MSocket;

//客户端套接字
class ClientSocketPool {
private:
	ClientSocketPool() = default;
	~ClientSocketPool() = default;

	ClientSocketPool(const ClientSocketPool&) = delete;
	ClientSocketPool& operator=(const ClientSocketPool&) = delete;
	ClientSocketPool(ClientSocketPool&&) = delete;
	ClientSocketPool& operator=(ClientSocketPool&&) = delete;

#ifdef _WIN32
	//WSADATA对象，用于向winsock注册本应用
	static WSADATA wsaData;
#endif

	//套接字数组
	static std::vector<SOCKET> socketPool;

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

	//创建socket
	static SOCKET creatSocket() noexcept;

	//销毁socket
	static void deleteSocket() noexcept;
private:
};

class MSocket final {
public:
	MSocket(const char* host, const char* port);
	~MSocket();

	MSocket(const MSocket&) = delete;
	MSocket& operator=(const MSocket&) = delete;
	MSocket(MSocket&&) = delete;
	MSocket& operator=(MSocket&&) = delete;

	void setHostAndPort(const char* host, const char* port) noexcept;
	void socketClose();
private:
	//socket对象
	SOCKET socket = INVALID_SOCKET;

	//sslsocket对象
	SSL* sslSocket = nullptr;

	//目标主机名
	std::string host;
	//目标端口号
	std::string port;

	//存储ip地址类型及协议相关信息
	struct addrinfo ipAddr;
	//存放DNS请求后的ip地址信息
	struct addrinfo* ipResult = nullptr;

	//选择SSL版本
	const SSL_METHOD* meth = SSLv23_client_method();
	//声明SSL上下文
	SSL_CTX* ctx = nullptr;

	//函数返回结果
	int result;
	//错误信息
	std::string errorLog;

	//ClientSocket静态类控制socket
	friend class ClientSocketPool;
};