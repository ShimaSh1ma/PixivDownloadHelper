﻿#include "HttpResponseParser.h"

#include <regex>

size_t HttpResponseParser::dealChunkData(std::string& bodyData) {
    size_t pos;
    size_t lastChunkSize = 0;
    do {
        // 找CRLF位置
        pos = bodyData.find("\r\n");
        if (pos == std::string::npos) {
            break;
        }
        // 获取块大小
        lastChunkSize = std::stoi(bodyData.substr(0, pos), nullptr, 16);
        // 判断块大小是否为零
        if (lastChunkSize == 0) {
            break;
        }
        // 判断剩余的块大小是否包含一整块
        if (lastChunkSize > bodyData.size()) {
            break;
        }
        // 将块大小信息机CRLF从data中去除
        bodyData = bodyData.substr(pos + 2);
        // 保存块信息
        this->payload.append(bodyData.substr(0, lastChunkSize));
        // 检查是否还有下一个块
        pos = bodyData.find("\r\n");
        if (pos != std::string::npos) {
            bodyData = bodyData.substr(pos + 2);
        } else {
            bodyData.clear();
        }
    } while (pos != std::string::npos);
    return lastChunkSize;
}

size_t HttpResponseParser::dealContentLength(std::string& bodyData) {
    this->payload.append(bodyData);
    bodyData.clear();
    if (size_t receivedLength = payload.length(); receivedLength < contentLength) {
        return contentLength - receivedLength;
    }
    return 0;
}

std::string HttpResponseParser::getHttpHead(const std::string& searchHeader) {
    auto iter = responseMap.find(searchHeader);
    return iter == responseMap.end() ? "" : iter->second;
}

void HttpResponseParser::operator()(const std::string& response) {
    std::regex rule1("HTTP/\\d(?:\\.\\d)? (\\d{3}) [A-Za-z ]+\\r\\n");
    std::smatch re;

    if (std::regex_search(response, re, rule1)) {
        this->statusCode = re[1];
        std::regex rule2("([A-Za-z\\-]+): ([\\S]+)\\r\\n");
        auto begin = response.cbegin();
        auto end = response.cend();
        while (std::regex_search(begin, end, re, rule2)) {
            this->responseMap.insert(std::pair<std::string, std::string>(re[1], re[2]));
            begin = re[0].second;
        }
    } else {
        statusCode = "-1";
    }

    std::string strContentLength = this->getHttpHead("Content-Length");
    contentLength = strContentLength == "" ? 0 : std::stoull(strContentLength);
}

std::string HttpResponseParser::getStatusCode() {
    return this->statusCode;
}

std::string HttpResponseParser::getPayload() {
    return this->payload;
}