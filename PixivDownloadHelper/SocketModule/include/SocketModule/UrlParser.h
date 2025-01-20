#pragma once

#include <string>

class UrlParser { // Url解析类
  public:
    std::string url;           // 完整URL
    std::string protocol;      // 网络协议
    std::string host;          // 主机
    std::string source;        // 资源地址
    std::string fileName;      // URL包含的的文件名
    std::string fileExtension; // 文件后缀

    void parseUrl(const std::string& url_input);

    explicit UrlParser() = default;
    ~UrlParser() = default;
};