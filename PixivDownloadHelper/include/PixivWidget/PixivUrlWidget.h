#pragma once

#include "BasicButton.h"
#include "BasicWidget.h"

// 输入url的窗口，含有一个文本框和下载按钮
class PixivUrlInputWidget final : public TranslucentWidget {
    Q_OBJECT
  public:
    explicit PixivUrlInputWidget();
    ~PixivUrlInputWidget() = default;

    PixivUrlInputWidget(const PixivUrlInputWidget&) = delete;
    PixivUrlInputWidget& operator=(const PixivUrlInputWidget&) = delete;
    PixivUrlInputWidget(PixivUrlInputWidget&&) = delete;
    PixivUrlInputWidget& operator=(PixivUrlInputWidget&&) = delete;
  signals:
    void inputUrlSignal(std::string); // 携带文本框内容的信号
  private:
    QHBoxLayout* layout;             // 水平布局
    PixivUrlEdit* textEdit;          // 文本框
    AnimationButton* downloadButton; // 下载按钮
};