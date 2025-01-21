#pragma once

#include "SettingWidget/SettingBackgroundWidget.h"
#include "SettingWidget/SettingCookieWidget.h"
#include "SettingWidget/SettingTargetPathWidget.h"
#include "SettingWidget/SettingTransparencyWidget.h"

// 用户设置窗口
class SubSettingWidget final : public TransparentWidget {
    Q_OBJECT
  public:
    explicit SubSettingWidget();   // 构造函数
    ~SubSettingWidget() = default; // 析构函数

    SubSettingWidget& operator=(const SubSettingWidget&) = delete;
    SubSettingWidget(const SubSettingWidget&) = delete;
    SubSettingWidget(SubSettingWidget&&) = delete;
    SubSettingWidget& operator=(SubSettingWidget&&) = delete;
  signals:
    void changeTransparencySliderValueChange(int value);
    void backgroundImgChanged();

  private:
    // 切换下载路径子窗口
    SettingTargetPathWidget* changeDirWidget;

    // 更改pixiv cookie子窗口
    SettingCookieWidget* changePixivCookieWidget;

    // 更改背景透明度子窗口
    SettingTransparencyWidget* changeTransparencyWidget;

    // 更改背景图片子窗口
    SettingBackgroundWidget* changeBackImageWidget;

    // 垂直布局
    QVBoxLayout* layout;
};

// 用户设置窗口（添加滚动）
class SettingWidget final : public TransparentWidget {
    Q_OBJECT
  public:
    explicit SettingWidget();
    ~SettingWidget() = default;

    SettingWidget& operator=(const SettingWidget&) = delete;
    SettingWidget(const SettingWidget&) = delete;
    SettingWidget(SettingWidget&&) = delete;
    SettingWidget& operator=(SettingWidget&&) = delete;
  signals:
    void changeTransparencySliderValueChange(int value);
    void backgroundImgChanged();

  private:
    // 窗口内容
    SubSettingWidget* subWidget;
    // 作为容器提供滚动条
    TransparentScrollArea* scrollArea;

    // 加入布局自适应窗口大小
    QVBoxLayout* layout;
};