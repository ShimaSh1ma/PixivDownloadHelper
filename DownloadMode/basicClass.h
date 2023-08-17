#ifndef _basicClass
#define _basicClass

/*
	文件名：basicClass.h
	功能：定义了爬虫需要的基本类型
	1、url解析类
	2、http报文组装类
	3、封装winsock类
*/
#include <qdebug.h>

#include "../GuiConstant.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <array>

#pragma comment(lib,"libssl.lib")
#pragma comment(lib,"libcrypto.lib")
#pragma comment(lib, "Ws2_32.lib")
class UrlParser {	//Url解析类
public:
	std::string url = "";			//完整URL
	std::string protocol = "";		//网络协议
	std::string host = "";			//主机
	std::string source = "";		//资源地址
	std::string fileName = "";		//URL包含的的文件名
	std::string fileExtension = "";	//文件后缀

	void parseUrl(const std::string& url_input);

	explicit UrlParser();
	~UrlParser();
};


class HttpRequest {	//http请求报文类
public:
	//资源路径
	std::string urlSource;
	//host头 主机名
	std::string urlHost;

	//请求方式，默认GET
	std::string method = "GET";
	//http版本,默认1.1
	std::string httpVersion = "HTTP/1.0";

	//Accept头
	std::string accept = "*/*";
	//Accept-Charset头
	std::string acceptCharset = "utf-8";
	//Accept-Language头
	std::string acceptLanguage = "zh-CN,zh;q=0.9";
	//Referer头
	std::string referer = "";
	//Cookie头
	std::string cookie = "";
	//User-agent头
	std::string userAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36";
	//Connection头
	std::string connection = "close";

	explicit HttpRequest(UrlParser& url);
	explicit HttpRequest();
	~HttpRequest() = default;

	void refreshUrl(UrlParser& url);

	//组装http请求报文
	std::string request();
};


class MSocket {	//封装win套接字
private:
	//创建WSADATA对象
	WSADATA wsaData{};
	//接收函数返回值，判断函数执行情况
	int _Result{};
	//存储ip地址类型及协议相关信息
	struct addrinfo ipAddr {};
	//存放DNS请求后的ip地址信息
	struct addrinfo* ipResult{};
	//创建socket对象
	SOCKET mySocket = INVALID_SOCKET;

	//选择SSL版本
	const SSL_METHOD* meth = SSLv23_client_method();
	//声明SSL上下文
	SSL_CTX* ctx;
	//声明sslsocket套接字
	SSL* sslSocket;

	//接收套接字相关函数返回值
	int result{};

	//错误信息字符串
	std::string log{ 0 };
	//更新错误信息
	inline void updateLog(const std::string& massage);
public:
	//返回错误信息
	std::string returnLog();

	//初始化socket套接字
	//（1._Host）：建立连接的目的服务器名
	//（2._Port）：指定访问服务器的端口号
	bool socketInit(const std::string& _Host, const std::string& _Port);

	//初始化ssl套接字
	bool sslInit();

	//连接到socket套接字
	bool sockConnect();

	//连接到ssl套接字
	bool sslConnect(const std::string& _Host);

	//向服务器发送信息
	//（1，sendbuf）：要向发送的信息字符串
	bool socketSend(const std::string& sendbuf);

	//关闭并释放socket套接字
	bool socketClose();

	//关闭并释放ssl套接字
	bool sslClose();

	//从服务器接收HTML源码
	std::string socketReceiveHtml();

	//从http报文中提取有效载荷
	//（1，file_dir）：下载文件存储地址
	bool socketReceiveFile(const std::string& file_dir);
};

#endif