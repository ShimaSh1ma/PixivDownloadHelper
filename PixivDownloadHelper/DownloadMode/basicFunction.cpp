#include"basicFunction.h"

std::string intToString(const int& a) {
	std::stringstream ss;
	std::string re;
	ss << a;
	ss >> re;
	return re;
}

void mkdir(const std::string& dir) {
	if (0 != _access(dir.c_str(), 0)) {		//检测是否存在路径,存在则返回0
		_mkdir(dir.c_str());					//不存在则创建本次下载路径
	}
}