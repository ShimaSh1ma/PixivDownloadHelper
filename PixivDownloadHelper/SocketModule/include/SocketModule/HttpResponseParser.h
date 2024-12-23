#pragma once

#include <string>
#include <map>

class HttpResponseParser {		//http响应报文解析类
public:
    // http响应状态码
    std::string statusCode;

    // 重载()运算符，实现获取http报文并解析
    void operator()(const std::string& response);
    // 通过 响应行头 获取 值
    std::string findKeyOfHeader(const std::string& header);

    explicit HttpResponseParser() = default;
    ~HttpResponseParser() = default;
private:
    // 用于存储解析后得到所有 响应行头 与 其对应的值
    std::map<std::string, std::string> responseMap;
};