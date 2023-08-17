#ifndef _publicFunctions
#define _publicFunctions

/*本文件中函数：
1、处理不同网站的原始url和真正资源url之间的映射关系
2、处理接收到的json文件中的转义字符
3、程序用的到各种类型转换、文件创建、文件删除等函数
*/

#include "Crawler.h"
#include <io.h>
#include <direct.h>

//简单处理json，删去json中的转义字符“\”
void jsonParse(std::string& json);

//将源url转化成pixiv.net的ajax接口url
std::string pixivAjaxurl(const std::string& url);

//从微博缩略图获取原图
std::string weiboUrl(const UrlParser& url);

//传入一个url集合vector数组下载其中文件
//（1、url）：含有多个url的vector
//（2、refer）：http报文中的referer头
void fileDownloadV(std::vector<std::string>& url, const std::string& refer = "");

//pixiv输入作品url下载所有图片
void pixivDownload_muti(const std::string& url);

////pixiv输入作者作品界面url，获取所有符合条件作品
////（1、url）：作者作品界面的url
////返回值为该url包含的所有作品url
//std::vector<std::string> getPixivIllustsUrl(const std::string& inputUrl);

#endif // !_public_functions