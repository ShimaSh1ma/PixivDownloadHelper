#pragma once

#include <map>
#include <string>

class UrlParser;

class HttpRequest { // http请求报文类
  public:
    explicit HttpRequest();
    ~HttpRequest() = default;

    // 设置连接目标主机及资源路径
    void setUrl(const UrlParser& url);
    void setUrl(const std::string& host, const std::string& source);

    // 设置http方法
    void setHttpMethod(const std::string& method);
    // 设置http版本
    void setHttpVersion(const std::string& version);

    // 添加或覆盖请求行
    void addHttpHead(const std::initializer_list<std::pair<std::string, std::string>>& lst);

    // 组装http请求报文
    std::string httpRequest();

  private:
    // http请求头
    std::map<std::string, std::string> httpHead;

    // http请求行
    struct HttpLine {
        // 资源路径
        std::string urlSource;
        // host头 主机名
        std::string urlHost;
        // 请求方式，默认GET
        std::string method = "GET";
        // http版本,默认1.1
        std::string httpVersion = "HTTP/1.1";
    } httpLine;

    // 组装请求行
    std::string constructHttpLine();

    // 组装请求头
    std::string constructHttpHead();
};