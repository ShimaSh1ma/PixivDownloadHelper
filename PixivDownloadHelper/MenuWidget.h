#ifndef _MenuWidget
#define _MenuWidget

#include "BasicWidget.h"
#include "BasicButton.h"
class MenuWidget : //菜单窗口
    public TranslucentWidget
{
public:
    MenuButton* pixivButton;//切换到pixiv下载界面按钮
    MenuButton* settingButton;//切换到设置界面按钮

    explicit MenuWidget();
    ~MenuWidget();
private:
};

#endif