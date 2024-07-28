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

void saveDownloadData(const std::string& data)
{
	auto f = [=]() {	
	std::ofstream o(_downloadDataFile, std::ios::app);
	if (o.is_open()) {
		o << data << "\n";
		o.close();
	}
	return; 
	};

	std::thread th(f);
	th.detach();
	return;
}

void deleteDownloadData(const std::string& data)
{
	auto f = [=]() {	
		std::string out;
		std::ifstream i(_downloadDataFile, std::ios::in);
		if (i.is_open()) {
			std::string temp{};
			std::string check{};
			while (std::getline(i, temp)) {
				check += temp + "\n";
				std::getline(i, temp);
				check += temp + "\n";
				if (check != (data + "\n")) {
					out += check;
				}
				check.clear();
			}
			i.close();
		}

		std::ofstream o(_downloadDataFile, std::ios::out);
		if (o.is_open()) {
			o << out;
			o.close();
		}

		return;
	};

	std::thread th(f);
	th.detach();
	return;
}

void saveFile(const std::string& dir, const std::string& data)
{
	std::ofstream out(dir, std::ios::binary);
	if (out.is_open()) {
		out << data;
		out.close();
	}
	return;
}
