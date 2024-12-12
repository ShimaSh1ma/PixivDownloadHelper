#include "BasicButton.h"

//AnimationButton
AnimationButton::AnimationButton(const QString& text,
	const QString& icon,
	const QSize& size) {
	//初始化组件
	iconLabel = std::make_unique<QLabel>();
	textLabel = std::make_unique<QLabel>();
	hoverAnimation = std::make_unique<QPropertyAnimation>(this, "color");
	layout = std::make_unique<QHBoxLayout>();

	//设置颜色
	buttonColor = _buttonNormal_color;

	//大小设置
	this->resize(size);

	//设置动画
	hoverAnimation->setDuration(200);
	hoverAnimation->setEasingCurve(QEasingCurve::OutCubic);

	//设置文字
	this->textLabel->setText(tr(text.toStdString().c_str()));
	this->textLabel->setFont(QFont("Microsoft YaHei", 9, 50));//设置字体：微软雅黑

	//设置图标
	if (icon != _EMPTY_STRING) {
		QPixmap pix(icon);
		//控制图标大小
		pix = pix.scaled(std::min(this->height(), this->width() * 3 / 4),
			std::min(this->height(), this->width() * 3 / 4),
			Qt::KeepAspectRatio, Qt::SmoothTransformation);
		this->iconLabel->setPixmap(pix);
	}

	//布局管理
	layout->setAlignment(Qt::AlignCenter);
	if (icon != _EMPTY_STRING && text != _EMPTY_STRING) {
		//同时具有图标和文字标签
		layout->addSpacing(this->width() / 20);
		layout->addWidget(iconLabel.release());
		layout->addSpacing(this->width() / 30);
		layout->addWidget(textLabel.release());
		layout->setAlignment(Qt::AlignLeft);
	}
	else if (icon != _EMPTY_STRING) {
		//只有图标
		layout->addWidget(iconLabel.release());
	}
	else if (text != _EMPTY_STRING) {
		//只有文字标签
		layout->addWidget(textLabel.release());
	}
	layout->setMargin(0);

	this->setLayout(layout.release());
}

void AnimationButton::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);//抗锯齿
	painter.setPen(Qt::NoPen);
	painter.setBrush(buttonColor);//按钮颜色
	if (isChecked()) {
		painter.setBrush(_buttonPressed_color);
	}

	QRect rt = this->rect();
	rt.setWidth(rt.width());
	rt.setHeight(rt.height());
	painter.drawRoundedRect(rt, 9, 9);//绘制圆角
}

void AnimationButton::enterEvent(QEvent* event) {
	setFocus();//设为焦点
	hoverAnimation->stop();
	hoverAnimation->setStartValue(this->color());
	hoverAnimation->setEndValue(_buttonHover_color);
	hoverAnimation->start();
}

void AnimationButton::leaveEvent(QEvent* event) {
	clearFocus();//清除焦点

	hoverAnimation->stop();
	hoverAnimation->setStartValue(this->color());
	hoverAnimation->setEndValue(_buttonNormal_color);
	hoverAnimation->start();
}

void AnimationButton::mousePressEvent(QMouseEvent* e) {
	hoverAnimation->stop();
	hoverAnimation->setStartValue(this->color());
	hoverAnimation->setEndValue(_buttonPressed_color);
	hoverAnimation->start();
}

void AnimationButton::mouseReleaseEvent(QMouseEvent* e) {
	hoverAnimation->stop();
	hoverAnimation->setStartValue(this->color());
	hoverAnimation->setEndValue(_buttonHover_color);
	hoverAnimation->start();
	emit click();
}

//MenuButton
MenuButton::MenuButton(const QString& label, const QString& icon, const QSize& size) :
	AnimationButton(label, icon, size) {
	//设置大小
	setFixedSize(_menuButton_size);

	setAutoExclusive(true);//设置互斥
	setCheckable(true);
	setFont(QFont("Microsoft YaHei"));//设置字体：微软雅黑

	//按钮按下发送对应窗口索引
	connect(this, &QPushButton::clicked, this, &MenuButton::getIndex);
}

void MenuButton::setIndex(int id) {
	this->index = id;
}

void MenuButton::getIndex() {
	emit indexSignal(this->index);
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

	connect(QApplication::clipboard(), &QClipboard::dataChanged,
		this, [this]() {
			if (QApplication::clipboard()->text() != this->text()) {
				this->clear();//清理文本框
				this->setText(QApplication::clipboard()->text());//将剪切板内容读取到文本框
				emit returnPressed();/*发送returnPressed()直接创建下载项目
									returnPressed()信号在PixivUrlWidget中绑定下载按钮按下click()信号*/
			}
		});//剪切板更改时，将剪切板内容读取到文本框
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