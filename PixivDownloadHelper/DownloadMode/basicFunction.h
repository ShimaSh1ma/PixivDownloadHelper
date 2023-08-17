#ifndef _basicFunction
#define	_basicFunction

/*该头文件中包含了程序用的到各种类型转换、文件创建、文件删除等函数*/

#include <string>
#include <sstream>
#include <io.h>
#include <direct.h>

//int类型转为string类型
std::string intToString(const int& a);

//创建文件夹
void mkdir(const std::string& dir);
#endif
