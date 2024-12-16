#include "DataProcess.h"

HttpRequest::HttpRequest(const UrlParser& url) : urlSource(url.source), urlHost(url.host) {}

void HttpRequest::remakeRequest(const UrlParser& url)
{
	this->urlHost = url.host;
	this->urlSource = url.source;
}

std::string HttpRequest::request() {
	std::string _url_host;
	std::string _accept;
	std::string _accept_charset;
	std::string _accept_language;
	std::string _referer;
	std::string _cookie;
	std::string _user_agent;
	std::string _connection;

	if (urlHost != "") {
		_url_host = "Host: " + urlHost + "\r\n";
	}
	if (accept != "") {
		_accept = "Accept: " + accept + "\r\n";
	}
	if (acceptCharset != "") {
		_accept_charset = "Accept-Charset: " + acceptCharset + "\r\n";
	}
	if (acceptLanguage != "") {
		_accept_language = "Accept-Language: " + acceptLanguage + "\r\n";
	}
	if (referer != "") {
		_referer = "Referer: " + referer + "\r\n";
	}
	if (cookie != "") {
		_cookie = "Cookie: " + cookie + "\r\n";
	}
	if (userAgent != "") {
		_user_agent = "User-Agent: " + userAgent + "\r\n";
	}
	if (connection != "") {
		_connection = "Connection: " + connection + "\r\n";
	}

	return method + " " + urlSource + " " + httpVersion + "\r\n"
		+ _url_host
		+ _accept
		+ _accept_charset
		+ _accept_language
		+ _referer
		+ _cookie
		+ _user_agent
		+ _connection
		+ "\r\n";
}