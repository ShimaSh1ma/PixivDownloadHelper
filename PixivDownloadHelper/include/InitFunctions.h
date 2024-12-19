#pragma once

#include <fstream>

#include <QtCore/qdebug.h>

#include "SocketModule/include/MSocket.h"
#include "SocketModule/include/basicFunction.h"

#include "GuiConstant.h"

void init();

void initDownloadPath();
void initPixivCookie();
void initBackgroundImagePath();
void initWindowTransparency();

void changeDownloadPath();
void changePixivCookie();
void changeBackgroundImagePath();
void changeWindowTransparency();