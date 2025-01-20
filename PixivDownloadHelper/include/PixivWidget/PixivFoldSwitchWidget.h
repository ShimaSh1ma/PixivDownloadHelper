#pragma once

#include "BasicButton.h"
#include "BasicWidget.h"

/*Pixiv下载窗口上方功能窗口，提供控制展开或折叠下载项目缩略图功能*/
class PixivDownloadTopWidget final : public TransparentWidget {
    Q_OBJECT
  public:
    explicit PixivDownloadTopWidget();
    ~PixivDownloadTopWidget() = default;

    PixivDownloadTopWidget(const PixivDownloadTopWidget&) = delete;
    PixivDownloadTopWidget& operator=(const PixivDownloadTopWidget&) = delete;
    PixivDownloadTopWidget(PixivDownloadTopWidget&&) = delete;
    PixivDownloadTopWidget& operator=(PixivDownloadTopWidget&&) = delete;
  signals:
    void foldButtonClicked();
    void unfoldButtonClicked();

  private:
    AnimationButton* foldButton;   // 折叠按钮，按下隐藏下载缩略图
    AnimationButton* unfoldButton; // 展开按钮，按下显示下载缩略图
    TextLabel* countLabel;         // 显示下载项目总数

    QHBoxLayout* layout; // 水平布局
};