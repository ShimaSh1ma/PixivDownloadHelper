#include "MenuWidget.h"
MenuWidget::MenuWidget(){
	//初始化组件
	pixivButton = new MenuButton("Pixiv", _icon_pixiv_path.c_str());
	settingButton = new MenuButton("Settings", _icon_setting_path.c_str());
	extendButton = new AnimationButton(nullptr, _icon_extend_path.c_str(), _extendButton_size);
	layout = new QVBoxLayout;
	sizeAnimation = new QPropertyAnimation(this, "fixedWidth");

	//设置默认按钮
	pixivButton->setChecked(true);
	//设置展开按钮
	extendButton->hide();
	extendButton->setFixedSize(_extendButton_size);

	//设置动画
	sizeAnimation->setDuration(200);
	sizeAnimation->setEasingCurve(QEasingCurve::OutCubic);

	//绑定扩展动画
	connect(this->extendButton, &AnimationButton::clicked,
		this, &MenuWidget::widgetExtend);
	
	//布局设置
	layout->addWidget(extendButton);

	layout->addWidget(pixivButton);
	layout->addWidget(settingButton);
	layout->addStretch(1);

	layout->setMargin(0);
	layout->setSpacing(0);
	this->setLayout(layout);

	//设置最小宽度
	this->setFixedWidth(_menuWidget_maxwidth
		+ layout->contentsMargins().left()
		+ layout->contentsMargins().right());
}

MenuWidget::~MenuWidget(){
	delete pixivButton;
	delete settingButton;
	delete sizeAnimation;
	delete extendButton;
	delete layout;
}

void MenuWidget::widgetExtend() {
	extendButton->hide();

	sizeAnimation->stop();
	sizeAnimation->setStartValue(this->width());
	sizeAnimation->setEndValue(_menuWidget_maxwidth
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