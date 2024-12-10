#pragma once

/*该头文件中包含了程序用的到各种类型转换、文件创建、文件删除等函数*/

#include <string>
#include <sstream>

#if defined(_WIN32)
#include <io.h>
#include <direct.h>
#endif

#if defined(__linux__)||defined(__APPLE__)

#endif

//int类型转为string类型
std::string intToString(const int& a);

//创建文件夹
void mkdir(const std::string& dir);
