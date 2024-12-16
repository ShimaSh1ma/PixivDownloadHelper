#include "basicFunction.h"

std::string intToString(const int& a) {
	std::stringstream ss;
	std::string re;
	ss << a;
	ss >> re;
	return re;
}

void mkdir(const std::string& dir) {
#if defined(_WIN32)
	if (_access(dir.c_str(), 0) != 0) {
		_mkdir(dir.c_str());
	}
#endif

#if defined(__APPLE__)||defined(__LINUX__)
	if (access(dir.c_str(), F_OK) != 0) {
		mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}
#endif
}