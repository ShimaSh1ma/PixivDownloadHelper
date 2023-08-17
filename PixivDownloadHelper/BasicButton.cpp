#include "BasicButton.h"
//MenuButton
MenuButton::MenuButton(const QString& label) :QPushButton(label) {
	setFixedSize(_menuButton_size);//设置大小

	setAutoExclusive(true);//设置互斥
	setCheckable(true);
	setFont(QFont("Microsoft YaHei"));//设置字体：微软雅黑

	//主菜单按钮样式
	setStyleSheet(
		"MenuButton:checked"	//选中时样式
		"{"
		"background-color:rgba(151,215,255,80);"
		"border:0px;"
		"border-radius:10px;"
		"}"
		"MenuButton:!checked"	//未选中时样式
		"{"
		"background-color:rgba(151,215,255,0);"
		"border:0px;"
		"}"
		"MenuButton:hover"
		"{"
		"background-color:rgba(151,215,255,50);"
		"border:0px;"
		"border-radius:10px;"
		"}"
		"MenuButton:pressed"
		"{"
		"background-color:rgba(151,215,255,120);"
		"border:0px;"
		"border-radius:10px;"
		"}"
		);
	//按钮按下发送对应窗口索引
	connect(this, &QPushButton::clicked, this, &MenuButton::getIndex);
}

void MenuButton::setIndex(int id) {
	this->index = id;
}

void MenuButton::getIndex() {
	emit ndexSignal(this->index);
}

//ToolButton
ToolButton::ToolButton(const QString& label) {
	this->setText(tr(label.toStdString().c_str()));
	setFixedSize(_pixivDownloadButton_size);//设置大小
	setFont(QFont("Microsoft YaHei"));//设置字体：微软雅黑
	//功能按钮样式
	setStyleSheet(
		"ToolButton"			//普通样式
		"{"
		"background-color:rgba(151,215,255,0);"
		"border:0px;"
		"border-radius:10px;"
		"}"
		"ToolButton:hover"		//鼠标悬浮时样式
		"{"
		"background-color:rgba(151,215,255,50);"
		"border:0px;"
		"border-radius:10px;"
		"}"
		"ToolButton:pressed"	//按下时样式
		"{"
		"background-color:rgba(151,215,255,150);"
		"border:0px;"
		"border-radius:10px;"
		"}"
	);

	setFont(QFont("Microsoft YaHei", 9, 50));//设置字体：微软雅黑
}

//TranslucentLineEdit
TranslucentLineEdit::TranslucentLineEdit() {
	setFrame(false);//无边框
	this->setStyleSheet(
		"border-radius:5px;"
		"background-color:rgba(255,255,255,0.4);"
		);//样式表设置圆角和背景色
	setFont(QFont("Microsoft YaHei", 8, 50));//设置字体：微软雅黑
}

//PixivUrlEdit
PixivUrlEdit::PixivUrlEdit() {
	//PixivUrlEdit文本框设置
	setFixedHeight(_pixivUrlLineEdit_size.height());//设置高度
	setPlaceholderText("https://www.pixiv.net/artworks/XXXXXXXXX");//背景提示
	//初始化剪切板
	clipboard = QApplication::clipboard();

	connect(clipboard, &QClipboard::dataChanged,
		this, &PixivUrlEdit::readClipboard);//剪切板更改时，将剪切板内容读取到文本框
}

void PixivUrlEdit::sendText() {
	emit TextS(this->text().toStdString());
}

void PixivUrlEdit::readClipboard() {
	if (clipboard->text() != this->text()) {
		this->clear();//清理文本框
		this->setText(clipboard->text());//将剪切板内容读取到文本框
		qDebug() << "returnPressed\r\n";
		emit returnPressed();/*发送returnPressed()直接创建下载项目
							returnPressed()信号在PixivUrlWidget中绑定下载按钮按下click()信号*/
	}
}

//DirEdit
DirEdit::DirEdit() {

}

//TransparentTextEdit
TransparentTextEdit::TransparentTextEdit() {
	setFrameStyle(NoFrame);//无边框
	this->setStyleSheet(
		"background-color:rgba(255,255,255,0);"
		);

	setFont(QFont("Microsoft YaHei", 8, 50));//设置字体：微软雅黑
	setAlignment(Qt::AlignLeft);//靠左显示
}

//textLabel
textLabel::textLabel() {
	setMinimumSize(_settingTitleLabel_size);//设置最小大小
	setFont(QFont("Microsoft YaHei", 10, 50));//设置字体：微软雅黑
	setAlignment(Qt::AlignLeft);//靠左显示
}

//ToolSlider
ToolSlider::ToolSlider() {
	setStyleSheet(
		"ToolSlider:groove:horizontal"
		"{"
		""
		"}"
		"ToolSlider:handle:horizontal"
		"{"
		"background-color:white;"
		"height:10px;"
		"width:10px;"
		"border-radius:5px;"
		"}"
	);
}

//bool ToolSlider::event(QEvent* event) {
//	if (event->type() == QEvent::Wheel) {
//		return true;
//	}
//	return false;
//}