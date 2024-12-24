#include "InitFunctions.h"

#include <fstream>

#include <QtCore/qdebug.h>

#include <SocketModule/ClientSocket.h>

#include "publicFunction.h"
#include "GuiConstant.h"

void init() {
	ClientSocket::WSAInit();
	mkdir("./config");
	initDownloadPath();
	initPixivCookie();
	initBackgroundImagePath();
	initWindowTransparency();
}

void initDownloadPath() {
	std::ifstream i(_config_download_save_path);
	if (i.is_open()) {
		std::getline(i, _downloadPath);
		i.close();
	}
}
void initPixivCookie() {
	std::ifstream i(_config_pixivcookie_save_path);
	if (i.is_open()) {
		std::getline(i, _pixivCookie);
		i.close();
	}
}
void initBackgroundImagePath() {
	std::ifstream i(_config_background_picture_path);
	if (i.is_open()) {
		std::getline(i, _backgroundPicturePath);
		i.close();
	}
}
void initWindowTransparency() {
	std::ifstream i(_config_window_tranparency_path);
	if (i.is_open()) {
		i >> _windowTransparency;
		i.close();
	}
}

void changeDownloadPath() {
	std::ofstream o(_config_download_save_path);
	if (o.is_open()) {
		o << _downloadPath;
		o.close();
	}
}
void changePixivCookie() {
	std::ofstream o(_config_pixivcookie_save_path);
	if (o.is_open()) {
		o << _pixivCookie;
		o.close();
	}
}
void changeBackgroundImagePath() {
	std::ofstream o(_config_background_picture_path);
	if (o.is_open()) {
		o << _backgroundPicturePath;
		o.close();
	}
}
void changeWindowTransparency() {
	std::ofstream o(_config_window_tranparency_path);
	if (o.is_open()) {
		o << _windowTransparency;
		o.close();
	}
}