#include"publicFunction.h"

std::string pixivAjaxurl(const std::string& url)
{
	std::regex get_id_rule("^https?://.+/(\\d+)");
	std::smatch r;

	if (std::regex_match(url, r, get_id_rule)) {
		return "https://www.pixiv.net/ajax/illust/" + (std::string)r[1] + "/pages?";
	}
	else {
		return "";
	}
}

void jsonParse(std::string& json)
{
	json.erase(std::remove(json.begin(), json.end(), '\\'), json.end());
}

std::string weiboUrl(const UrlParser& URL)
{
	std::string _Host = URL.host;
	std::string _Source = URL.source;
	std::string _Protocol = URL.protocol;
	std::string _Extension = URL.fileExtension;
	std::string _Id = {};
	std::regex gethost_dir_regex("^https?://[^/:]+/[^/]+([^.]+)(.+)");
	std::smatch r;

	if (std::regex_match(URL.url, r, gethost_dir_regex)) {
		_Id = r[1];
	}
	else {
		return "";
	}

	return  _Protocol + "://" + _Host + "/large" + _Id + _Extension;
}

void fileDownloadV(std::vector<std::string>& url, const std::string& refer) {
	std::string file_path = _downloadPath;		
	std::vector<std::string>::iterator it = url.begin();	//存放url的vector迭代器
	std::vector<std::string> retry;			//暂时存放需要重新下载url的vector

	while (it != url.end()) {

		UrlParser P_url;
		P_url.parseUrl(*it);

		std::string filename;
		filename = file_path + "\\" + P_url.fileName;

		HttpRequest hr(P_url);
		hr.referer = refer;
		hr.accept = "image/*";

		MHttpDownload M_thread;

		if (!M_thread.fileDownload_nonreuse(P_url, filename, hr.request())) {
			retry.push_back(*it);
		}
		else {
		}
		it++;
	}

	url = retry;
}

void pixivDownload_muti(const std::string& url) {
	std::string refer = url;		//原url作为refer

	//pixiv ajax接口url生成
	std::string* ajaxurl = new std::string;
	*ajaxurl = pixivAjaxurl(url);
	if (*ajaxurl == "") {
		delete ajaxurl;
		return; }

	UrlParser* urlP = new UrlParser;
	urlP->parseUrl(*ajaxurl);
	delete ajaxurl;

	//组装请求json文件报文
	HttpRequest* hr = new HttpRequest(*urlP);
	hr->referer = refer;
	hr->accept = "*/*";
	hr->acceptCharset = "";
	hr->cookie = _pixivCookie;
	MHttpDownload* M = new MHttpDownload;
	//请求json文件
	std::string* json = new std::string;
	*json = M->requestHtml(*urlP, hr->request());
	if (*json == _EMPTY_STRING) {

		delete json;
		delete M;
		delete hr;
		delete urlP;
		return;
	}
	else {
		delete hr;
		delete urlP;
	}
	//去除json文件中的转义字符
	jsonParse(*json);
	//提取图片url
	std::vector<std::string> Vurl;				//存放url的向量数组
	int total = M->parseHtmlForUrl(*json, Vurl, _regex_pixiv_illust_url);
	delete json;
	delete M;

	if (!Vurl.empty()) {
		fileDownloadV(Vurl,refer);
	}

	return;
}