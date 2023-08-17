#include "Crawler.h"

int MHttpDownload::parseHtmlForUrl(const std::string& html, std::vector<std::string>& U, const std::string& rule)
{
		std::regex geturl_pattern(rule);
		int count = 0;

		const std::sregex_token_iterator end;
		for (std::sregex_token_iterator iter(html.begin(), html.end(), geturl_pattern); iter != end; ++iter)
		{
			U.push_back(iter->str());
			++count;
		}
		return count;
}


std::string MHttpDownload::requestHtml(const UrlParser& URL, const std::string& request)
{
	std::string http = _EMPTY_STRING;			//接收报文字符串

	std::string _Host = URL.host;
	std::string _Source = URL.source;
	std::string _Protocol = URL.protocol;
	std::string _Port;
	if (_Protocol == "https") {
		_Port = "443";
	}
	else if(_Protocol == "http"){
		_Port = "80";
	}
	else {
		return _EMPTY_STRING;
	}

	if (socketInit(_Host,_Port)) {
		if (sslInit()) {
			if (sockConnect()) {
				if (sslConnect(_Host)) {
					std::string* sendbuffer = new std::string(request);
					if (socketSend(*sendbuffer)) {
						delete sendbuffer;
						http = socketReceiveHtml();
						sslClose();
						socketClose();
					}
				}
			}
		}
	}
	return http;
}

bool MHttpDownload::fileDownload_nonreuse(const UrlParser& URL, const std::string& download_dir, const std::string& request)
{
	std::string _Host = URL.host;
	std::string _Source = URL.source;
	std::string _Protocol = URL.protocol;
	std::string _Port;
	if (_Protocol == "https") {
		_Port = "443";
	}
	else if (_Protocol == "http") {
		_Port = "80";
	}
	else {
		return false;
	}

	if (socketInit(_Host, _Port)) {
		if (sslInit()) {
			if (sockConnect()) {
				if (sslConnect(_Host)) {
					std::string* sendbuffer = new std::string(request);
					if (socketSend(*sendbuffer)) {
						delete sendbuffer;
						socketReceiveFile(download_dir);
						sslClose();
						socketClose();
					}
				}
			}
		}
	}
	if (returnLog() != _DOWNLOAD_SUCCESS){
		return false;
	}
	return true;
}