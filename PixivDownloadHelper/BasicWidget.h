#pragma once
#ifndef _BasicWidget
#define _BasicWidget

#include <QtWidgets/qwidget.h>
#include <QtGui/qpainter.h>
#include <QtGui/qpalette.h>
#include <QtGui/qcolor.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qscrollarea.h>

#include "GuiConstant.h"
/* 基础窗口样式类 */
class TransparentWidget ://无边框透明窗口
    public QWidget
{
public:
    explicit TransparentWidget();
    ~TransparentWidget();
private:
    virtual void paintEvent(QPaintEvent* paintE);//重写绘制事件，实现窗口透明
};

class TranslucentWidget ://无边框圆角半透明窗口
    public QWidget
{
public:
    explicit TranslucentWidget();//构造函数，用于设置窗口无边框
    ~TranslucentWidget() = default;//析构函数
private:
    virtual void paintEvent(QPaintEvent* paintE);//重写绘制事件，实现窗口半透明及圆角
};

class TransparentScrollArea ://透明滚动区域
    public QScrollArea
{
public:

    explicit TransparentScrollArea();
    ~TransparentScrollArea();
private:
};

#endif