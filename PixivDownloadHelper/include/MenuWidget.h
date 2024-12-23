#pragma once

#include <QtWidgets/qsizepolicy.h>

#include "BasicWidget.h"
#include "BasicButton.h"

class MenuWidget : //菜单窗口
    public TransparentWidget
{
    Q_OBJECT;

    Q_PROPERTY(int fixedWidth READ width WRITE setFixedWidth);
public:
    explicit MenuWidget();
    ~MenuWidget() = default;

    void bindPixivButton(int index);
    void bindSettingButton(int index);
public slots:
    void widgetExtend();
    void widgetFold();
signals:
    void menuButtonIndexSignal(int _index);
private:
    template<typename T>void bindButtonSignal(const T& button);

    MenuButton* pixivButton;//切换到pixiv下载界面按钮
    MenuButton* settingButton;//切换到设置界面按钮

    AnimationButton* extendButton;//展开按钮

    QVBoxLayout* layout;//布局

    std::unique_ptr<QPropertyAnimation> sizeAnimation;//展开折叠动画
};