#pragma once

#include <string>
#include <map>

class HttpResponseParser {		//http响应报文解析类
public:
    explicit HttpResponseParser() = default;
    ~HttpResponseParser() = default;

    // 重载()运算符，实现获取http报文并解析
    void operator()(const std::string& response);
    // 通过 响应行头 获取 值
    std::string getHttpHead(const std::string& header);
    // 获取http状态码
    std::string getStatusCode();
private:
    // 用于存储解析后得到所有 响应行头 与 其对应的值
    std::map<std::string, std::string> responseMap;
    // http响应状态码
    std::string statusCode = "-1";
};