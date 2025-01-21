#pragma once

#include "BasicButton.h"
#include "BasicWidget.h"

// 输入url的窗口，含有一个文本框和下载按钮
class PixivUrlWidget final : public TranslucentWidget {
    Q_OBJECT
  public:
    explicit PixivUrlWidget();
    ~PixivUrlWidget() = default;

    PixivUrlWidget(const PixivUrlWidget&) = delete;
    PixivUrlWidget& operator=(const PixivUrlWidget&) = delete;
    PixivUrlWidget(PixivUrlWidget&&) = delete;
    PixivUrlWidget& operator=(PixivUrlWidget&&) = delete;
  signals:
    void inputUrlSignal(std::string); // 携带文本框内容的信号
  private:
    QHBoxLayout* layout;             // 水平布局
    PixivUrlEdit* textEdit;          // 文本框
    AnimationButton* downloadButton; // 下载按钮
};