#pragma once
#ifndef _BasicWidget
#define _BasicWidget

#include <qdebug.h>

#include <QtWidgets/qwidget.h>
#include <QtGui/qpainter.h>
#include <QtGui/qpalette.h>
#include <QtGui/qcolor.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qscrollarea.h>
#include <QtWidgets/qscrollbar.h>
#include <QtGui/qevent.h>
#include <QtCore/qpropertyanimation.h>
#include <QtCore/qparallelanimationgroup.h>
#include <QtWidgets/qstackedwidget.h>
#include <QtWidgets/qgraphicseffect.h>

#include "GuiConstant.h"
/* 基础窗口样式类 */
class TransparentWidget ://无边框透明窗口
    public QWidget
{
public:
    explicit TransparentWidget();
    ~TransparentWidget() = default;
private:
    virtual void paintEvent(QPaintEvent* paintE) override;//重写绘制事件，实现窗口透明
};

class TranslucentWidget ://无边框圆角半透明窗口
    public QWidget
{
public:
    explicit TranslucentWidget();//构造函数，用于设置窗口无边框
    ~TranslucentWidget() = default;//析构函数
private:
    virtual void paintEvent(QPaintEvent* paintE) override;//重写绘制事件，实现窗口半透明及圆角
};

class TransparentScrollArea ://透明滚动区域
    public QScrollArea
{
public:

    explicit TransparentScrollArea();
    ~TransparentScrollArea();
private:
    QPropertyAnimation* scrollAnimation;
protected:
    void wheelEvent(QWheelEvent* wheelEvent) override;
    void keyPressEvent(QKeyEvent* ev) override;
};

class StackedWidget :
    public QStackedWidget
{
    Q_OBJECT
public:
    explicit StackedWidget();
    ~StackedWidget();
public slots:
    void switchWidget(int _index);//切换动画
    void setWidget();//切换动画完成后显示窗口
signals:
    void enterSignal();
private:
    QPropertyAnimation* posAnimation;//切换动画：位置动画
    QPropertyAnimation* opacityAnimation;//切换动画：透明度动画
    QGraphicsOpacityEffect* opacityEffect;//透明度遮罩

    QParallelAnimationGroup* switchGroup;//切换动画组

    int index;//当前页面索引
protected:
    virtual void enterEvent(QEvent* event); //重写进入事件，发送信号
};

class PressWidget :
    public TranslucentWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
public:
    explicit PressWidget();
    ~PressWidget();
private:

    QColor backGroundColor;//背景颜色，用于实现鼠标悬浮时的窗口变色效果
    inline QColor color() { return this->backGroundColor; }//获取按钮颜色
    inline void setColor(const QColor& color) {
        this->backGroundColor = color;
        repaint();
        return;
    }//设置颜色

    QPropertyAnimation* hoverAnimation;//鼠标悬浮动画

    virtual void paintEvent(QPaintEvent* paintE) override;//重写绘制事件实现悬浮动画
    virtual void enterEvent(QEvent* event) override;//重写鼠标进入事件
    virtual void leaveEvent(QEvent* event) override;//重写鼠标离开事件
};

#endif