﻿#pragma once

/*本文件中函数：
1、处理不同网站的原始url和真正资源url之间的映射关系
2、处理接收到的json文件中的转义字符
3、程序用的到各种类型转换、文件创建、文件删除等函数
*/

#include <string>
#include <vector>

class UrlParser;

// 创建文件夹
void mkdir(const std::string& dir);

// 简单处理json，删去json中的转义字符“\”
void jsonParse(std::string& json);

// 从html中解析出图片url
std::vector<std::string> parserHtml(const std::string& html, const std::string& regex);

// 将源url转化成pixiv.net的ajax接口url
std::string pixivAjaxurl(const std::string& url);

// 从微博缩略图获取原图
std::string weiboUrl(const UrlParser& url);

// 保存添加的下载信息
void saveDownloadData(const std::string& data);

// 删除已完成的下载信息
void deleteDownloadData(const std::string& data);

// 保存文件
void saveFile(const std::string& dir, const std::string& data);

// 处理跨平台中文编码问题
std::string processChineseCodec(const std::string& str);