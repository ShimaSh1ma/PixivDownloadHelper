#pragma once

#include <map>
#include <string>

class ClientSocket;

class HttpResponseParser { // http响应报文解析类
  public:
    explicit HttpResponseParser() = default;
    ~HttpResponseParser() = default;

    // 解析http报头
    void parseResponse(const std::string& response);
    // 使用chunked接收数据，处理chunked块传输数据,将处理后数据保存入payload变量，返回最后一个chunk块大小
    size_t recvByChunckedData(std::string& bodyData);
    // 使用contentlength接收数据，返回剩余要读取的长度
    size_t recvByContentLength(std::string& bodyData);
    // 通过 响应行头 获取 值
    std::string getHttpHead(const std::string& header);
    // 获取http状态码
    std::string getStatusCode();
    // 获取载荷
    std::string getPayload();

  private:
    // 用于存储解析后得到所有 响应行头 与 其对应的值
    std::map<std::string, std::string> responseMap;
    // contentlength
    size_t contentLength = 0;
    // http响应状态码
    std::string statusCode = "-1";
    // 响应载荷
    std::string payload = "";
};