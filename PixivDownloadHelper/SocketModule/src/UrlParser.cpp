#include "UrlParser.h"

#include <regex>

void UrlParser::parseUrl(const std::string& url_input) {
    // 完整URL
    this->url = url_input;

    // 网络协议、主机名、资源路径
    std::regex get_protocol_rule("^(https?)://([^/:]+)(.+)");
    std::smatch r1;

    if (std::regex_match(url_input, r1, get_protocol_rule)) {
        this->protocol = r1[1].str();
        this->host = r1[2].str();
        this->source = r1[3].str();

        // URL包含的文件名和后缀
        std::regex get_filename_rule("/([^/]+?)(\\.[\\w]+)?$");
        std::smatch r2;

        if (std::regex_search(this->source, r2, get_filename_rule)) {
            this->fileName = r2[1].str();
            this->fileExtension = r2[2].str();
        } else {
            this->fileName = "";
            this->fileExtension = "";
        }
    } else {
        this->protocol = "";
        this->host = "";
        this->source = "";
    }
}