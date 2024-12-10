#pragma once

/* ��������ʼ�����������ú���
1����������·�����û�cookie������ͼƬ���Զ������ã�init��ͷ������
2����������·�����û�cookie������ͼƬ���Զ������ã�change��ͷ������*/

#include <fstream>

#include <QtCore/qdebug.h>

#include "MSocket.h"

#include "GuiConstant.h"

//��ʼ������
void init();

void initDownloadPath();//��������·��
void initPixivCookie();//����pixivcookie
void initBackgroundImagePath();//���ر���ͼƬ·��
void initWindowTransparency();//���ر���͸����

//�������ú���
void changeDownloadPath();
void changePixivCookie();
void changeBackgroundImagePath();
void changeWindowTransparency();