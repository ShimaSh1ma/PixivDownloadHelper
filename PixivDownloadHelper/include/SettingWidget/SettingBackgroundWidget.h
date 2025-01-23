#pragma once

#include "BasicButton.h"
#include "BasicWidget.h"

// 更改背景图片的窗口
class SettingBackgroundWidget final : public TranslucentWidget {
    Q_OBJECT
  public:
    explicit SettingBackgroundWidget();
    ~SettingBackgroundWidget() = default;

    SettingBackgroundWidget(const SettingBackgroundWidget&) = delete;
    SettingBackgroundWidget& operator=(const SettingBackgroundWidget&) = delete;
    SettingBackgroundWidget(SettingBackgroundWidget&&) = delete;
    SettingBackgroundWidget& operator=(SettingBackgroundWidget&&) = delete;

  signals:
    void backgroundImgChanged(); // 发送背景Í改变信号通知主窗口刷新
  private:
    void chooseImage(); // 打开资源管理器并选择背景图片，更新背景图片设置文件backgroundPicture.cfg
    void removeImage(); // 移除背景图片
    TextLabel* title;
    // 背景图片预览窗口
    QLabel* imageView;
    // 按钮
    AnimationButton* changeButton; // 切换按钮
    AnimationButton* removeButton; // 移除按钮

    // 网格布局
    QGridLayout* layout;
};
