#ifndef _InitFunction
#define _InitFunction
/* 定义程序初始化及更改设置函数
1、加载下载路径、用户cookie、背景图片等自定义设置（init开头函数）
2、更改下载路径、用户cookie、背景图片等自定义设置（change开头函数）*/

#include <fstream>
#include <qdebug.h>
#include <DownloadMode\MSocket.h>
#include "GuiConstant.h"

//初始化函数
void init();

void initDownloadPath();//加载下载路径
void initPixivCookie();//加载pixivcookie
void initBackgroundImagePath();//加载背景图片路径
void initWindowTransparency();//加载背景透明度

//更改设置函数
void changeDownloadPath();
void changePixivCookie();
void changeBackgroundImagePath();
void changeWindowTransparency();

#endif