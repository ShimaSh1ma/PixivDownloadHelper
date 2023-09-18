#include "NetworkClass.h"

HttpResponseParser::HttpResponseParser() {
	responseVector = new std::vector<HeaderLine>;//堆上开辟空间存储解析后数据
	responseVector->reserve(20);				//预开辟20个元素空间
	httpResponse = new std::string;
	*httpResponse = _EMPTY_STRING;
	statusCode = _EMPTY_STRING;
}

HttpResponseParser::~HttpResponseParser() {
	delete responseVector;
	delete httpResponse;
}

std::string HttpResponseParser::findKeyOfHeader(const std::string& searchHeader) {
	auto end = this->responseVector->end();
	//循环匹配，找到对应 响应行头 则返回值，未找到则返回空字符串
	for (auto begin = this->responseVector->begin(); begin < end; ++begin) {
		if (begin->header == searchHeader) {
			return begin->key;
		}
	}
	return _EMPTY_STRING;
}

void HttpResponseParser::operator()(const std::string& response) {
	//存储完整响应报文头
	*(this->httpResponse) = response;
	//解析http响应报文头
	parseHttpResponse();
}

void HttpResponseParser::parseHttpResponse() {
	std::regex rule1("HTTP/[\\d]{1}\\.[\\d]{1} ([\\d]+) [\\w]+\\r\\n");
	std::smatch re;

	if (std::regex_search(*(this->httpResponse), re, rule1)) {	//第一层匹配状态码
		this->statusCode = re[1];
		//第二层循环匹配响应中的响应头和其对应值
		std::regex rule2("([A-Za-z\\-]+): ([\\S]+)[\\r\\n]+");
		//初始化响应报文头尾指针
		auto begin = this->httpResponse->cbegin();
		auto end = this->httpResponse->cend();
		//循环匹配所有报文头
		while (std::regex_search(begin, end, re, rule2)) {
			this->responseVector->emplace_back(HeaderLine{ re[1],re[2] });
			begin = re[0].second;
		}
		return;
	}
	//未匹配到状态码则置空并返回
	else {
		statusCode = _EMPTY_STRING;
		return;
	}
}