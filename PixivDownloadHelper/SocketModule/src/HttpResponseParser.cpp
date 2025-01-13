#include "HttpResponseParser.h"

#include <regex>

std::string HttpResponseParser::getHttpHead(const std::string& searchHeader) {
	auto iter = responseMap.find(searchHeader);
	return iter == responseMap.end() ? "" : iter->second;
}

void HttpResponseParser::operator()(const std::string& response) {
	std::regex rule1("HTTP/\\d(?:\\.\\d)? (\\d{3}) \\w+\\r\\n");
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
	}
	else {
		statusCode = "-1";
	}
}

std::string HttpResponseParser::getStatusCode() {
	return this->statusCode;
}