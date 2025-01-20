#pragma once

#include "PixivFoldSwitchWidget.h"
#include "PixivItemContainerWidget.h"
#include "PixivUrlWidget.h"

// 用scrollarea提供滚动条显示PixivDownloadItemWidget
class PixivDownloadWidget final : public TransparentWidget {
    Q_OBJECT
  public:
    explicit PixivDownloadWidget();
    ~PixivDownloadWidget() = default;

    PixivDownloadWidget(const PixivDownloadWidget&) = delete;
    PixivDownloadWidget& operator=(const PixivDownloadWidget&) = delete;
    PixivDownloadWidget(PixivDownloadWidget&&) = delete;
    PixivDownloadWidget& operator=(PixivDownloadWidget&&) = delete;

    void checkUrl(const std::string& url);
    // 窗口重绘
    void onChangedRepaint();
  signals:
    void sizeChangedSignal();

  private:
    // pixiv下载上方窗口
    PixivDownloadTopWidget* topWidget;
    // pixiv下载项目总览窗口
    PixivDownloadItemWidget* itemWidget;
    // 作为容器提供滚动条
    TransparentScrollArea* scrollArea;
    // 加入布局自适应窗口大小
    QVBoxLayout* layout;

    int wWidth = 0; // 记录窗口宽度做缓冲
    void virtual resizeEvent(QResizeEvent* ev);
};

// pixiv下载界面
class PixivWidget final : public TransparentWidget {
  public:
    explicit PixivWidget();
    ~PixivWidget() = default;

    PixivWidget(const PixivWidget&) = delete;
    PixivWidget& operator=(const PixivWidget&) = delete;
    PixivWidget(PixivWidget&&) = delete;
    PixivWidget& operator=(PixivWidget&&) = delete;

    // 切换窗口时重绘
    void onChangedRepaint();

  private:
    // 垂直布局
    QVBoxLayout* layout;
    // 包含的窗口
    PixivUrlInputWidget* inputWidget;
    PixivDownloadWidget* downloadWidget;
};