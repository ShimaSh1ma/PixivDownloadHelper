#pragma once

#include <string>

class UrlParser;

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
    std::string referer;
    //Cookie头
    std::string cookie;
    //User-agent头
    std::string userAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36";
    //Connection头
    std::string connection = "close";

    explicit HttpRequest(const UrlParser& url);
    explicit HttpRequest() = default;
    ~HttpRequest() = default;

    //传入新的url组装报文
    void remakeRequest(const UrlParser& url);

    //组装http请求报文
    std::string request();
};