#pragma once
#ifndef _BasicButton
#define _BasicButton
/* 定义基本的组件样式类 */
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qtextedit.h>
#include <QtWidgets/qapplication.h>
#include <QtGui/qpainter.h>
#include <QtGui/qclipboard.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qslider.h>
#include "GuiConstant.h"

#include <qdebug.h>
/* 按钮样式 */
class MenuButton ://主菜单按钮，互斥
	public QPushButton
{
	Q_OBJECT

private:
	int index{};//按钮对应窗口索引
public slots:
	void getIndex();//按钮按下时执行，发出带索引的showIndex()信号
signals:
	void ndexSignal(int);//发送索引的信号
public:
	explicit MenuButton(const QString& label);
	~MenuButton() = default;

	void setIndex(int id);//传入对应窗口索引
};

class ToolButton ://功能按钮
	public QPushButton
{
	Q_OBJECT
public:
	explicit ToolButton(const QString& label);
	~ToolButton() = default;
private:
};

/* 单行文本框样式 */
class TranslucentLineEdit ://半透明圆角文本框
	public QLineEdit
{
public:

	explicit TranslucentLineEdit();
	~TranslucentLineEdit() = default;
private:
};

class PixivUrlEdit ://pixiv url输入文本框
	public TranslucentLineEdit
{
	Q_OBJECT

public slots:
	void sendText();//发送Text()信号的槽函数
	void readClipboard();//读取剪切板
signals:
	void TextS(std::string);//携带文本框内容的信号
public:
	QClipboard* clipboard;//剪切板对象

	explicit PixivUrlEdit();
	~PixivUrlEdit() = default;
private:
};

class DirEdit ://显示下载路径文本框
	public TranslucentLineEdit
{
public:
	DirEdit();
	~DirEdit() = default;
};

/* 文本编辑框 */
class TransparentTextEdit ://透明多行文本框
	public QTextEdit
{
public:

	explicit TransparentTextEdit();
	~TransparentTextEdit() = default;
private:
};

/* 自定义标签 */
class textLabel :	//文字标签
	public QLabel
{
public:
	explicit textLabel();
	~textLabel() = default;
private:
};

class ToolSlider :
	public QSlider
{
public:

	explicit ToolSlider();
	~ToolSlider() = default;

	//virtual bool event(QEvent* event) override;//重载滚轮操作，忽视滚轮
private:
};

#endif