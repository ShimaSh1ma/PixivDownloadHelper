﻿#include "MenuWidget.h"
MenuWidget::MenuWidget() :TranslucentWidget() {
	//设置窗口大小
	setFixedSize(_menuWidget_size);

	//初始化按钮成员
	pixivButton = new MenuButton("Pixiv");
	settingButton = new MenuButton("Settings");
	//设置父窗口
	pixivButton->setParent(this);
	settingButton->setParent(this);
	//设置默认按钮
	pixivButton->setChecked(true);

	//按钮位置调整
	settingButton->move(0, _menuButton_size.height());

	//显示按钮
	pixivButton->show();
	settingButton->show();
}

MenuWidget::~MenuWidget(){
	delete pixivButton;
	delete settingButton;
}