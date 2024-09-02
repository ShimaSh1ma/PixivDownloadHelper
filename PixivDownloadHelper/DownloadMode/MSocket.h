#pragma once
#ifndef _NetworkClass
#define _NetworkClass

/*
	文件名：basicClass.h
	功能：定义了爬虫需要的基本类型
	1、url解析类
	2、http报文组装类
	3、封装winsock类
*/
#include <qdebug.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include <vector>
#include <string>

#include "DataProcess.h"

#pragma comment(lib,"libssl.lib")
#pragma comment(lib,"libcrypto.lib")
#pragma comment(lib,"Ws2_32.lib")

//——————————————异常检查宏常量定义———————————————
#define _M_WSASTART_ERR				"WSAStartup Error"			//winsock环境初始化异常
#define _M_DNS_ERR					"DNS Error"					//域名转换异常
#define _M_SOCKET_CREATE_ERR		"Socket Create Error"		//创建winsock套接字失败
#define _M_SOCKET_CONNECT_ERR		"Socket Connect Error"		//连接到服务器失败
#define _M_SOCKET_CLOSE_ERR			"Socket Close Error"		//关闭winsock套接字失败

#define _M_SSL_CONTEXT_ERR			"SSL_CTX_new Error"			//ssl上下文建立失败
#define _M_SSL_CREATE_ERR			"SSL New Error"				//ssl套接字创建失败
#define _M_SSL_CONNECT_ERR			"SSL Connect error"			//ssl握手失败
#define _M_SSL_WRITE_ERR			"SSL Write Error"			//ssl发送信息失败

#define _DOWNLOAD_ERR				"Download Error"			//下载文件失败
#define	_DOWNLOAD_SUCCESS			"Download Success"			//下载文件成功
#define _REQUEST_ERR				"Request Error"				//请求页面失败
#define _REQUEST_SUCCESS			"Request Success"			//请求页面成功

#define _FILE_OPEN_ERR				"Error Open "				//文件打开失败
#define _FILE_CREATE_ERR			"Error Create "				//文件创建失败

#define _EMPTY_STRING				""							//空字符串
//——————————————————————————————————————

class MSocket;

//客户端套接字
class ClientSocket {
private:
	//WSADATA对象，用于向winsock注册本应用
	static WSADATA wsaData;

	//套接字数组
	static std::vector<MSocket> socketPool;

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
	static std::string socketReceive() noexcept;

	//断开连接并关闭套接字
	static void sslDisconnectToServer(MSocket& _socket) noexcept;

	//创建socket
	static SOCKET creatSocket() noexcept;

	//销毁socket
	static void deleteSocket() noexcept;
private:
};

WSADATA ClientSocket::wsaData = {};

class MSocket final{
public:
	MSocket() = delete;
	MSocket(const char* host, const char* port);

	void setHostAndPort(const char* host, const char* port) noexcept;

private:
	//socket对象
	SOCKET socket = INVALID_SOCKET;
	//sslsocket对象
	SSL* sslSocket = nullptr;

	//目标主机名
	std::string host = {};
	//目标端口号
	std::string port = {};

	//存储ip地址类型及协议相关信息
	struct addrinfo ipAddr = {};
	//存放DNS请求后的ip地址信息
	struct addrinfo* ipResult = nullptr;

	//选择SSL版本
	const SSL_METHOD* meth = SSLv23_client_method();
	//声明SSL上下文
	SSL_CTX* ctx = nullptr;

	//缓冲区大小
	int bufSize;

	//函数返回结果
	int result;
	//错误信息
	std::string errorLog = {};

	//ClientSocket静态类控制socket
	friend class ClientSocket;
};

#endif