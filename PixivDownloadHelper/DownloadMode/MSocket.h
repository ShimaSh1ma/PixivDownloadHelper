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

#include <sys/types.h>  // 提供数据类型，比如 ssize_t
#include <sys/socket.h> // 提供 socket 函数和数据结构
#include <netinet/in.h> // 提供字节顺序转换函数和结构体，比如 sockaddr_in
#include <arpa/inet.h>  // 提供 IP 地址转换函数，比如 inet_pton 和 inet_ntop
#include <unistd.h>     // 提供 close() 函数
#include <netdb.h>      // 提供网络数据库操作的函数，比如 getaddrinfo

using SOCKET = int;
constexpr const int INVALID_SOCKET = -1;
constexpr const int SOCKET_ERROR = -1;

#define SD_SEND SHUT_WR
#define SD_RECEIVE SHUT_RD
#define SD_BOTH SHUT_RDWR

#define WSAGetLastError() (errno)

#endif 

constexpr const size_t _socket_buffer_size{ 1024 * 4 };

#include <vector>
#include <string>

#include "DataProcess.h"

//——————————————异常检查宏常量定义———————————————
constexpr const char* _M_WSASTART_ERR = "WSAStartup Error";
constexpr const char* _M_DNS_ERR = "DNS Error";
constexpr const char* _M_SOCKET_CREATE_ERR = "Socket Create Error";
constexpr const char* _M_SOCKET_CONNECT_ERR = "Socket Connect Error";
constexpr const char* _M_SOCKET_CLOSE_ERR = "Socket Close Error";

constexpr const char* _M_SSL_CONTEXT_ERR = "SSL_CTX_new Error";
constexpr const char* _M_SSL_CREATE_ERR = "SSL New Error";
constexpr const char* _M_SSL_CONNECT_ERR = "SSL Connect error";
constexpr const char* _M_SSL_WRITE_ERR = "SSL Write Error";

constexpr const char* _DOWNLOAD_ERR = "Download Error";
constexpr const char* _DOWNLOAD_SUCCESS = "Download Success";
constexpr const char* _REQUEST_ERR = "Request Error";
constexpr const char* _REQUEST_SUCCESS = "Request Success";

constexpr const char* _FILE_OPEN_ERR = "Error Open ";
constexpr const char* _FILE_CREATE_ERR = "Error Create ";
//——————————————————————————————————————

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
	static void sslConnectToServer(MSocket& _socket) noexcept;

	//向服务器发送信息
	static void socketSend(MSocket& _socket, const std::string& sendbuf) noexcept;

	//从服务器接收报文
	static std::string socketReceive(MSocket& _socket) noexcept;

	//断开连接并关闭套接字
	static void sslDisconnectToServer(MSocket& _socket) noexcept;

	//创建socket
	static SOCKET creatSocket() noexcept;

	//销毁socket
	static void deleteSocket() noexcept;
private:
};

#ifdef _WIN32
WSADATA ClientSocketPool::wsaData = {};
#endif

class MSocket final {
public:
	MSocket(const char* host, const char* port);
	~MSocket();

	MSocket(const MSocket&) = delete;
	MSocket& operator=(const MSocket&) = delete;
	MSocket(MSocket&&) = delete;
	MSocket& operator=(MSocket&&) = delete;

	void setHostAndPort(const char* host, const char* port) noexcept;
	void socketClean();
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