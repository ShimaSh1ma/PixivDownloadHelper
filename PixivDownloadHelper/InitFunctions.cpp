#include "InitFunctions.h"

void init() {
	initDownloadPath();
	initPixivCookie();
	initBackgroundImagePath();
	initWindowTransparency();
}

void initDownloadPath() {
	std::ifstream i(_config_download_save_path);
	if (i.is_open()) {
		i >> _downloadPath;
		i.close();
	}
	else {
		qDebug() << "������·�������ļ�ʧ��\r\n";
	}
}
void initPixivCookie() {
	std::ifstream i(_config_pixivcookie_save_path);
	if (i.is_open()) {
		std::getline(i, _pixivCookie);
		i.close();
	}
	else {
		qDebug() << "��cookie�����ļ�ʧ��\r\n";
	}
}
void initBackgroundImagePath() {
	std::ifstream i(_config_background_picture_path);
	if (i.is_open()) {
		i >> _backgroundPicturePath;
		i.close();
	}
	else {
		qDebug() << "�򿪱���ͼƬ�����ļ�ʧ��\r\n";
	}
}
void initWindowTransparency() {
	std::ifstream i(_config_window_tranparency_path);
	if (i.is_open()) {
		i >> _windowTransparency;
		i.close();
	}
	else {
		qDebug() << "�򿪱���͸���������ļ�ʧ��\r\n";
	}
}

void changeDownloadPath() {
	std::ofstream o(_config_download_save_path);
	if (o.is_open()) {
		o << _downloadPath;
		o.close();
	}
	else {
		qDebug() << "��������·������ʧ��\r\n";
	}
}
void changePixivCookie() {
	std::ofstream o(_config_pixivcookie_save_path);
	if (o.is_open()) {
		o << _pixivCookie;
		o.close();
	}
	else {
		qDebug() << "����cookie����ʧ��\r\n";
	}
}
void changeBackgroundImagePath() {
	std::ofstream o(_config_background_picture_path);
	if (o.is_open()) {
		o << _backgroundPicturePath;
		o.close();
	}
	else {
		qDebug() << "���±���ͼƬ·������ʧ��\r\n";
	}
}
void changeWindowTransparency() {
	std::ofstream o(_config_window_tranparency_path);
	if (o.is_open()) {
		o << _windowTransparency;
		o.close();
	}
	else {
		qDebug() << "���±�����͸��������ʧ��\r\n";
	}
}