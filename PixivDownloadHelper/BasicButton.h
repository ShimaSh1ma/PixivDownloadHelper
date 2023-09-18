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
#include <QtWidgets/qscrollbar.h>
#include <QtWidgets/qlayout.h>
#include <QtCore/qpropertyanimation.h>
#include <QtGui/qevent.h>

#include "GuiConstant.h"

#include <qdebug.h>
/* 按钮样式 */
class AnimationButton ://动画按钮
	public QPushButton
{
	Q_OBJECT

	Q_PROPERTY(QColor color READ color WRITE setColor)
public:
	explicit AnimationButton(const QString& text = nullptr,
		const QString& icon = nullptr,
		const QSize& size = { 0,0 });
	~AnimationButton();

	inline QColor color() { return this->buttonColor; }//获取按钮颜色
	inline void setColor(const QColor& color) {
		this->buttonColor = color;
		repaint();
		return;
	}//设置颜色

	QLabel* iconLabel;//图标标签
	QLabel* textLabel;//文字标签
	QHBoxLayout* layout;//水平布局
private:
	QColor buttonColor;//按钮颜色
	QPropertyAnimation* hoverAnimation;//鼠标进入动画

	virtual void paintEvent(QPaintEvent* event) override;//重写绘制事件
	virtual void enterEvent(QEvent* event) override;//重写鼠标进入事件
	virtual void leaveEvent(QEvent* event) override;//重写鼠标离开事件
	virtual void mousePressEvent(QMouseEvent* e) override;//重写鼠标按下事件
	virtual void mouseReleaseEvent(QMouseEvent* e) override;//重写鼠标释放事件
};

class MenuButton ://主菜单按钮，互斥
	public AnimationButton
{
	Q_OBJECT
public:
	explicit MenuButton(const QString& label = nullptr,
		const QString& icon = nullptr,
		const QSize& size = _menuButton_size);
	~MenuButton() = default;

	void setIndex(int id);//传入对应窗口索引
public slots:
	void getIndex();//按钮按下时执行，发出带索引的showIndex()信号
signals:
	void indexSignal(int);//发送索引的信号
private:
	int index{};//按钮对应窗口索引
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
	~TransparentTextEdit();
private:
	QPropertyAnimation* scrollAnimation;
protected:
	virtual void enterEvent(QEvent* event) override;//enter事件触发setfocus
	virtual void leaveEvent(QEvent* event) override;//leave事件触发clearfocus
	virtual void wheelEvent(QWheelEvent* wheelEvent) override;	//滚轮实现平滑动画
	virtual void keyPressEvent(QKeyEvent* ev) override;			//按键平滑动画
	virtual bool eventFilter(QObject* obj, QEvent* ev) override;//过滤滚轮事件，不透射到其他窗口
};

/* 自定义标签 */
class TextLabel :	//文字标签
	public QLabel
{
public:
	explicit TextLabel();
	~TextLabel() = default;
private:
};

/* 滚动条 */
class Slider :
	public QSlider
{

protected:
	void wheelEvent(QWheelEvent* wheelE) override;
};

#endif