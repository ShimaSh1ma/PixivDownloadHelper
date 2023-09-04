#include "MenuWidget.h"
MenuWidget::MenuWidget() :TranslucentWidget() {
	this->setMaximumSize(_menuWidget_maxsize);
	//初始化按钮成员
	pixivButton = new MenuButton("Pixiv", _icon_pixiv_path.c_str());
	settingButton = new MenuButton("Settings", _icon_setting_path.c_str());
	layout = new QVBoxLayout;

	//设置默认按钮
	pixivButton->setChecked(true);
	
	//布局设置
	layout->addWidget(pixivButton);
	layout->addWidget(settingButton);

	layout->setMargin(0);
	layout->setSpacing(0);
	this->setLayout(layout);
}

MenuWidget::~MenuWidget(){
	delete pixivButton;
	delete settingButton;
	delete layout;
}