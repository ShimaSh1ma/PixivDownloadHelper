#pragma once

#include "BasicButton.h"
#include "BasicWidget.h"

// 更改背景图片透明度的窗口
class SettingTransparencyWidget final : public TranslucentWidget {
    Q_OBJECT
  public:
    explicit SettingTransparencyWidget();
    ~SettingTransparencyWidget() = default;

    SettingTransparencyWidget(const SettingTransparencyWidget&) = delete;
    SettingTransparencyWidget& operator=(const SettingTransparencyWidget&) = delete;
    SettingTransparencyWidget(SettingTransparencyWidget&&) = delete;
    SettingTransparencyWidget& operator=(SettingTransparencyWidget&&) = delete;
  public slots:
    void saveTranparency(); // 保存透明度设置
  signals:
    void sliderValueChange(int value);

  private:
    // 标题标签
    TextLabel* title;
    // 滑动条
    Slider* slider;
    // 网格布局
    QGridLayout* layout;
};
