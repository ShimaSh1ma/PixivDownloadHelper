#include "InitFunctions.h"

#include <fstream>

#include <SocketModule/ClientSocket.h>

#include "GuiConstant.h"
#include "publicFunction.h"

void init() {
    WSAInit();
    mkdir("./config");
    initDownloadPath();
    initPixivCookie();
    initBackgroundImagePath();
    initWindowTransparency();
}

void initDownloadPath() {
    std::ifstream i(CONFIG_FILE_SAVE_PATH);
    if (i.is_open()) {
        std::getline(i, _downloadPath);
        i.close();
    }
}
void initPixivCookie() {
    std::ifstream i(CONFIG_PIXIV_COOMKIE_PATH);
    if (i.is_open()) {
        std::getline(i, _pixivCookie);
        i.close();
    }
}
void initBackgroundImagePath() {
    std::ifstream i(CONFIG_BG_PIC_PATH);
    if (i.is_open()) {
        std::getline(i, _backgroundPicturePath);
        i.close();
    }
}
void initWindowTransparency() {
    std::ifstream i(CONFIG_WINDOW_TRANSPARENCY_PATH);
    if (i.is_open()) {
        i >> _windowTransparency;
        i.close();
    }
}

void changeDownloadPath() {
    std::ofstream o(CONFIG_FILE_SAVE_PATH);
    if (o.is_open()) {
        o << _downloadPath;
        o.close();
    }
}
void changePixivCookie() {
    std::ofstream o(CONFIG_PIXIV_COOMKIE_PATH);
    if (o.is_open()) {
        o << _pixivCookie;
        o.close();
    }
}
void changeBackgroundImagePath() {
    std::ofstream o(CONFIG_BG_PIC_PATH);
    if (o.is_open()) {
        o << _backgroundPicturePath;
        o.close();
    }
}
void changeWindowTransparency() {
    std::ofstream o(CONFIG_WINDOW_TRANSPARENCY_PATH);
    if (o.is_open()) {
        o << _windowTransparency;
        o.close();
    }
}