﻿#pragma once
#include <string>
#include <regex>
#include <vector>

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
	std::string httpVersion = "HTTP/1.1";

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

	explicit HttpRequest(const UrlParser& url);
	explicit HttpRequest();
	~HttpRequest() = default;

	//传入新的url组装报文
	void refreshUrl(const UrlParser& url);

	//组装http请求报文
	std::string request();
};

class HttpResponseParser {		//http响应报文解析类
public:
	//定义结构体存储一对 响应头部 与 其对应的值
	struct HeaderLine {
		std::string header;
		std::string key;
	};
	//string指针，堆上存储完整http响应报文头
	std::string* httpResponse;
	//http响应状态码
	std::string statusCode;

	void operator()(const std::string& response);//重载()运算符，实现获取http报文并解析

	std::string findKeyOfHeader(const std::string& header);//通过 响应行头 获取 值

	explicit HttpResponseParser();
	~HttpResponseParser();
private:
	/*用于存储解析后得到所有 响应行头 与 其对应的值
	动态数组指针	*/
	std::vector<HeaderLine>* responseVector;

	void parseHttpResponse();//解析http响应
};
