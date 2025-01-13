#include "HttpRequest.h"
#include "UrlParser.h"
#include <vector>

HttpRequest::HttpRequest() : httpHead{
		{"accept","*/*"},
		{"acceptCharset","utf-8"},
		{"acceptLanguage","zh-CN,zh;q=0.9"},
		{"referer",""},
		{"cookie",""},
		{"userAgent","Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36"},
		{"connection","keep-alive"}
} {
}

std::string HttpRequest::constructHttpLine() {
	return
		httpLine.method + " " +
		httpLine.urlSource + " " +
		httpLine.httpVersion + "\r\n";
}

std::string HttpRequest::constructHttpHead() {
	std::string retStr;
	for (auto it : this->httpHead) {
		retStr += it.first + ": " + it.second + "\r\n";
	}
	return retStr;
}

void HttpRequest::setUrl(const std::string& host, const std::string& source) {
	this->httpLine.urlHost = host;
	this->httpLine.urlSource = source;
}

void HttpRequest::setUrl(const UrlParser& url)
{
	this->setUrl(url.host, url.source);
}

void HttpRequest::setHttpMethod(const std::string& method) {
	this->httpLine.method = method;
}

void HttpRequest::setHttpVersion(const std::string& version) {
	this->httpLine.httpVersion = version;
}

void HttpRequest::addHttpHead(const std::pair<std::string, std::string>& newHead) {
	this->httpHead.insert(newHead);
}

std::string HttpRequest::httpRequest() {
	return this->constructHttpLine() + this->constructHttpHead() + "\r\n";
}