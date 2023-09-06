#include "BasicButton.h"
//MenuButton
MenuButton::MenuButton(const QString& label, const QString& icon) {
	//初始化组件
	iconLabel = new QLabel;
	textLabel = new QLabel;
	layout = new QHBoxLayout;

	//设置图标
	QPixmap pix(icon);
	pix = pix.scaled(24, 24, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	iconLabel->setPixmap(pix);
	//设置文字
	textLabel->setText(tr(label.toStdString().c_str()));
	textLabel->setFont(QFont("Microsoft YaHei", 9, 50));//设置字体：微软雅黑

	setFixedSize(_menuButton_maxsize);//设置大小

	setAutoExclusive(true);//设置互斥
	setCheckable(true);
	setFont(QFont("Microsoft YaHei"));//设置字体：微软雅黑

	//布局管理
	layout->addSpacing(this->width() / 10);
	layout->addWidget(iconLabel);
	layout->addSpacing(this->width() / 10);
	layout->addWidget(textLabel);
	layout->addStretch(1);
	layout->setMargin(0);

	this->setLayout(layout);

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
		"background-color:rgba(151,215,255,80);"
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

MenuButton::~MenuButton() {
	delete iconLabel;
	delete textLabel;
	delete layout;
}

void MenuButton::setIndex(int id) {
	this->index = id;
}

void MenuButton::getIndex() {
	emit indexSignal(this->index);
}

//ToolButton
ToolButton::ToolButton(const QString& label, const QString& icon) {
	//设置图标
	this->setIconSize(QSize(24, 24));
	this->setIcon(QIcon(icon));
	//设置文字
	this->setText(tr(label.toStdString().c_str()));
	this->setFixedSize(_pixivDownloadButton_size);//设置大小
	this->setFont(QFont("Microsoft YaHei", 9, 50));//设置字体：微软雅黑
	//功能按钮样式
	setStyleSheet(
		"ToolButton"			//普通样式
		"{"
		"background-color:rgba(100,100,100,20);"
		"border:0px;"
		"border-radius:6px;"
		"}"
		"ToolButton:hover"		//鼠标悬浮时样式
		"{"
		"background-color:rgba(151,215,255,50);"
		"border:0px;"
		"border-radius:6px;"
		"}"
		"ToolButton:pressed"	//按下时样式
		"{"
		"background-color:rgba(151,215,255,150);"
		"border:0px;"
		"border-radius:6px;"
		"}"
	);
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

	//初始化滚动动画
	scrollAnimation = new QPropertyAnimation(this->verticalScrollBar(), "value");
	scrollAnimation->setDuration(200);
	scrollAnimation->setEasingCurve(QEasingCurve::OutCubic);

	this->setStyleSheet(
		"background-color:rgba(255,255,255,0);"
		);

	this->verticalScrollBar()->setStyleSheet(
		"QScrollBar:vertical{"
		"background-color:transparent;"
		"width:10px;"
		"}"
		"QScrollBar:handle:vertical{"
		"background:rgba(220,220,220,255);"
		"border-radius:5px;"
		"}"
		"QScrollBar:handle:vertical:hover{"
		"background:rgba(200,200,200,255);"
		"border-radius:5px;"
		"}"
		"QScrollBar:add-page:vertical{"
		"background-color:transparent;"
		"}"
		"QScrollBar:sub-page:vertical{"
		"background-color:transparent;"
		"}"
		"QScrollBar:sub-line:vertical{"
		"background:none;"
		"border:none;"
		"color:none;"
		"}"
		"QScrollBar:add-line:vertical{"
		"background:none;"
		"border:none;"
		"color:none;"
		"}"
	);

	setFont(QFont("Microsoft YaHei", 8, 50));//设置字体：微软雅黑
	setAlignment(Qt::AlignLeft);//靠左显示
}

TransparentTextEdit::~TransparentTextEdit() {
	delete scrollAnimation;
}

void TransparentTextEdit::enterEvent(QEvent* event) {
	setFocus();
}

void TransparentTextEdit::leaveEvent(QEvent* event) {
	clearFocus();
}

void TransparentTextEdit::wheelEvent(QWheelEvent* wheelEvent) {
	scrollAnimation->stop();
	scrollAnimation->setEndValue(this->verticalScrollBar()->value() - wheelEvent->angleDelta().y());
	scrollAnimation->start();
}

void TransparentTextEdit::keyPressEvent(QKeyEvent* ev) {
	scrollAnimation->stop();
	int changeValue{ 0 };
	if (ev->key() == Qt::Key_Up) {
		changeValue = _pixivDownloadItemWithoutPre_height;
	}
	else if (ev->key() == Qt::Key_Down) {
		changeValue = -_pixivDownloadItemWithoutPre_height;
	}
	else if (ev->key() == Qt::Key_PageUp) {
		changeValue = _pixivDownloadItemWithPre_height + 5;
	}
	else if (ev->key() == Qt::Key_PageDown) {
		changeValue = -_pixivDownloadItemWithPre_height - 5;
	}
	else {}

	scrollAnimation->setEndValue(this->verticalScrollBar()->value() - changeValue);
	scrollAnimation->start();
}

bool TransparentTextEdit::eventFilter(QObject* obj, QEvent* ev) {
	if (this->hasFocus()) {
		if (ev->type() == QEvent::Wheel) {
			return true;
		}
	}
	return false;
}

//TextLabel
TextLabel::TextLabel() {
	setMinimumSize(_settingTitleLabel_size);//设置最小大小
	setFont(QFont("Microsoft YaHei", 10, 50));//设置字体：微软雅黑
	setAlignment(Qt::AlignLeft);//靠左显示
}

//Slider
void Slider::wheelEvent(QWheelEvent* wheelE) {

}