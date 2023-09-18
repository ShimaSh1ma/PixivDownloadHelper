#include "NetworkClass.h"

HttpResponseParser::HttpResponseParser() {
	responseVector = new std::vector<HeaderLine>;//���Ͽ��ٿռ�洢����������
	responseVector->reserve(20);				//Ԥ����20��Ԫ�ؿռ�
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
	//ѭ��ƥ�䣬�ҵ���Ӧ ��Ӧ��ͷ �򷵻�ֵ��δ�ҵ��򷵻ؿ��ַ���
	for (auto begin = this->responseVector->begin(); begin < end; ++begin) {
		if (begin->header == searchHeader) {
			return begin->key;
		}
	}
	return _EMPTY_STRING;
}

void HttpResponseParser::operator()(const std::string& response) {
	//�洢������Ӧ����ͷ
	*(this->httpResponse) = response;
	//����http��Ӧ����ͷ
	parseHttpResponse();
}

void HttpResponseParser::parseHttpResponse() {
	std::regex rule1("HTTP/[\\d]{1}\\.[\\d]{1} ([\\d]+) [\\w]+\\r\\n");
	std::smatch re;

	if (std::regex_search(*(this->httpResponse), re, rule1)) {	//��һ��ƥ��״̬��
		this->statusCode = re[1];
		//�ڶ���ѭ��ƥ����Ӧ�е���Ӧͷ�����Ӧֵ
		std::regex rule2("([A-Za-z\\-]+): ([\\S]+)[\\r\\n]+");
		//��ʼ����Ӧ����ͷβָ��
		auto begin = this->httpResponse->cbegin();
		auto end = this->httpResponse->cend();
		//ѭ��ƥ�����б���ͷ
		while (std::regex_search(begin, end, re, rule2)) {
			this->responseVector->emplace_back(HeaderLine{ re[1],re[2] });
			begin = re[0].second;
		}
		return;
	}
	//δƥ�䵽״̬�����ÿղ�����
	else {
		statusCode = _EMPTY_STRING;
		return;
	}
}