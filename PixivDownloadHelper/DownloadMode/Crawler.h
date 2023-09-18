#ifndef _Crawler
#define _Crawler

#include "NetworkClass.h"
#include <qdebug.h>
#include <vector>

class MHttpDownload :
	public MSocket {
public:

	//正则匹配解析HTML得到图片URL
	//返回值表示总计图片个数
	//（1，html）：html字符串
	//（2，url）：存放url的VECTOR向量，需要预先开辟空间
	//（3，rule）：正则匹配规则
	int parseHtmlForUrl(const std::string& html,
		std::vector<std::string>& url,
		const std::string& rule = "https?://[^\"]+.(jpg|png)");

	//请求HTML页面
	// 返回值为Html字符串
	//（1，URL）目标url
	//（2，request）发送的http报文
	std::string requestHtml(const UrlParser& URL, const std::string& request);

	//下载文件，不复用TCP连接，每接受一个文件重新握手
	//（1，URL）目标url
	//（2，file_dir）图片文件存储路径
	//（3，request）发送的http报文
	bool fileDownload_nonreuse(const UrlParser& url,
		const std::string& download_dir,
		const std::string& request);
};
#endif // !_clawer