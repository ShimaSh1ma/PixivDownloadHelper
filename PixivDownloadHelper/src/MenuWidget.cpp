#include "MenuWidget.h"

MenuWidget::MenuWidget() {
	//初始化组件
	pixivButton = new MenuButton("Pixiv", _icon_pixiv_path);
	settingButton = new MenuButton("Settings", _icon_setting_path);
	extendButton = new AnimationButton(nullptr, _icon_extend_path, _extendButton_size);
	layout = new QVBoxLayout();
	sizeAnimation = std::make_unique<QPropertyAnimation>(this, "fixedWidth");

	//设置默认按钮
	pixivButton->setChecked(true);
	//设置展开按钮
	extendButton->hide();
	extendButton->setFixedSize(_extendButton_size);

	//设置动画
	sizeAnimation->setDuration(200);
	sizeAnimation->setEasingCurve(QEasingCurve::OutCubic);

	//绑定扩展动画
	connect(this->extendButton, &QPushButton::clicked,
		this, &MenuWidget::widgetExtend);

	//绑定按钮按下，发送携带选中序号的信号
	bindButtonSignal(pixivButton);
	bindButtonSignal(settingButton);

	//设置最小宽度
	this->setFixedWidth(_menuWidget_maxwidth
		+ layout->contentsMargins().left()
		+ layout->contentsMargins().right());

	//布局设置
	layout->addWidget(extendButton);

	layout->addWidget(pixivButton);
	layout->addWidget(settingButton);
	layout->addStretch(1);

	layout->setMargin(0);
	layout->setSpacing(0);
	this->setLayout(layout);
}

template<typename T>void MenuWidget::bindButtonSignal(const T& button) {
	static_assert(std::is_base_of<MenuButton, T>::value, "button不是MenuButton及其子类");
	connect(button, &MenuButton::clicked, this, [this, button]() {emit menuButtonIndexSignal(button->getIndex());});
}

void MenuWidget::bindPixivButton(int index) {
	pixivButton->setIndex(index);
}

void MenuWidget::bindSettingButton(int index) {
	settingButton->setIndex(index);
}

void MenuWidget::widgetExtend() {
	extendButton->hide();

	sizeAnimation->stop();
	sizeAnimation->setStartValue(this->width());
	sizeAnimation->setEndValue(static_cast<int64_t>(_menuWidget_maxwidth)
		+ layout->contentsMargins().left()
		+ layout->contentsMargins().right());
	sizeAnimation->start();

	pixivButton->show();
	settingButton->show();
}

void MenuWidget::widgetFold() {
	pixivButton->hide();
	settingButton->hide();

	sizeAnimation->stop();
	sizeAnimation->setStartValue(this->width());
	sizeAnimation->setEndValue(_extendButton_size.width()
		+ layout->contentsMargins().left()
		+ layout->contentsMargins().right());
	sizeAnimation->start();

	extendButton->show();
}