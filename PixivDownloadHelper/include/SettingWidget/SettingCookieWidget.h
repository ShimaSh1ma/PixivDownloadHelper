#pragma once

#include "BasicButton.h"
#include "BasicWidget.h"

// 更改PixivCookie的窗口
class SettingCookieWidget final : public TranslucentWidget {
    Q_OBJECT
  public:
    explicit SettingCookieWidget();
    ~SettingCookieWidget() = default;

    SettingCookieWidget(const SettingCookieWidget&) = delete;
    SettingCookieWidget& operator=(const SettingCookieWidget&) = delete;
    SettingCookieWidget(SettingCookieWidget&&) = delete;
    SettingCookieWidget& operator=(SettingCookieWidget&&) = delete;
  public slots:
    void saveCookie();   // 更改_pixivCookie,并设置pixiv cookie文本框为只读
    void turnEditable(); // 设置pixiv cookie文本框可编辑
  private:
    // 标题标签
    TextLabel* title;
    // 显示当前cookie的文本框
    TransparentTextEdit* textEdit;
    // 更改按钮
    AnimationButton* changeButton;
    // 保存更改按键
    AnimationButton* saveButton;

    // 网格布局
    QGridLayout* layout;

    bool showOrNot = false; // 窗口显示或隐藏状态位
  protected:
    virtual void mousePressEvent(QMouseEvent* mouseE) override; // 重写鼠标点击事件，实现窗口显示或隐藏
};
