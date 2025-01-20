#include "HttpRequest.h"
#include "UrlParser.h"

#include <initializer_list>
#include <vector>

HttpRequest::HttpRequest()
    : httpHead{{"Host", ""},
               {"Accept", "*/*"},
               {"Accept-Charset", "utf-8"},
               {"Accept-Language", "zh-CN,zh;q=0.9"},
               {"Referer", ""},
               {"Cookie", ""},
               {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) "
                              "Chrome/114.0.0.0 Safari/537.36"},
               {"Connection", "keep-alive"}} {
}

std::string HttpRequest::constructHttpLine() {
    return httpLine.method + " " + httpLine.urlSource + " " + httpLine.httpVersion + "\r\n";
}

std::string HttpRequest::constructHttpHead() {
    std::string retStr;
    for (auto it : this->httpHead) {
        if (it.second != "") {
            retStr += it.first + ": " + it.second + "\r\n";
        }
    }
    return retStr;
}

void HttpRequest::setUrl(const std::string& host, const std::string& source) {
    this->httpLine.urlHost = host;
    this->httpLine.urlSource = source;
    this->addHttpHead({{"Host", host}});
}

void HttpRequest::setUrl(const UrlParser& url) {
    this->setUrl(url.host, url.source);
}

void HttpRequest::setHttpMethod(const std::string& method) {
    this->httpLine.method = method;
}

void HttpRequest::setHttpVersion(const std::string& version) {
    this->httpLine.httpVersion = version;
}

void HttpRequest::addHttpHead(const std::initializer_list<std::pair<std::string, std::string>>& lst) {
    for (auto pair : lst) {
        this->httpHead[pair.first] = pair.second;
    }
}

std::string HttpRequest::httpRequest() {
    return this->constructHttpLine() + this->constructHttpHead() + "\r\n";
}
