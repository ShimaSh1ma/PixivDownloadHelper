﻿#pragma once

#include "BasicButton.h"
#include "BasicWidget.h"

#include <functional>

/*pixiv下载项目标题窗口， 由若干label组成*/
class PixivItemTitle final : public TransparentWidget {
  public:
    explicit PixivItemTitle(const std::string& str);
    ~PixivItemTitle() = default;

  private:
    TextLabel* urlLabel; // 显示url的标签
    QHBoxLayout* layout; // 水平布局
};

// pixiv下载项目缩略图窗口
class PixivItemPreview final : public TransparentWidget {
  public:
    explicit PixivItemPreview();
    ~PixivItemPreview() = default;

    PixivItemPreview(const PixivItemPreview&) = delete;
    PixivItemPreview& operator=(const PixivItemPreview&) = delete;
    PixivItemPreview(PixivItemPreview&&) = delete;
    PixivItemPreview& operator=(PixivItemPreview&&) = delete;

    void loadPreviewImage(const std::string& imagePath); // 加载缩略图
  private:
    QLabel* previewImage; // 缩略图
    QHBoxLayout* layout;  // 水平布局

    std::string previewImagePath = DEFAULT_PREVIEW_PATH; // 缩略图路径
};

// pixiv下载项目下载状态窗口
class PixivItemState final : public TransparentWidget {
  public:
    explicit PixivItemState();
    ~PixivItemState() = default;

    PixivItemState(const PixivItemState&) = delete;
    PixivItemState& operator=(const PixivItemState&) = delete;
    PixivItemState(PixivItemState&&) = delete;
    PixivItemState& operator=(PixivItemState&&) = delete;

    void setState(const downloadState& _state);             // 设置下载状态
    void setProgress(const int& total, const int& success); // 设置下载进度
  private:
    TextLabel* downloadStateLabel; // 显示下载状态的标签
    TextLabel* totalCountLabel;    // 显示总图片数的标签
    TextLabel* separatorLabel;     // 显示分隔符
    TextLabel* successCountLabel;  // 显示下载成功图片数的标签

    QHBoxLayout* layout; // 水平布局

    int imageCount = 0;   // 总图片数
    int successCount = 0; // 下载成功数

    downloadState state = downloadState::WAITING; // 默认为等待状态
    QString downloadStateString();                // 根据状态枚举量返回下载状态字符串
};

// pixiv下载项目
class PixivItemWidget final : public PressWidget {
  public:
    explicit PixivItemWidget(const std::string& _url, const std::string& _path, const bool& foldOrUnfold = true);
    ~PixivItemWidget() = default;

    PixivItemWidget(const PixivItemWidget&) = delete;
    PixivItemWidget& operator=(const PixivItemWidget&) = delete;
    PixivItemWidget(PixivItemWidget&&) = delete;
    PixivItemWidget& operator=(PixivItemWidget&&) = delete;

    std::string getUrl();
    std::string getPath();

    // 下载完成回调
    std::function<void(const std::string&, const std::string&)> completeFunction;

    void previewWidgetVisiable(bool visiable); // 设置缩略图显示隐藏
    void checkUrlType();                       // 检查url类型

  private:
    PixivItemTitle* titleWidget;     // 标题窗口
    PixivItemPreview* previewWidget; // 缩略图窗口
    PixivItemState* stateWidget;     // 下载状态窗口
    QVBoxLayout* layout;             // 垂直布局

    void pixivDownload();    // pixiv下载函数
    void telegramDownload(); // telegram下载函数

    std::string downloadUrl;                                          // 下载URL
    const std::string downloadPath;                                   // 下载路径
    virtual void mouseDoubleClickEvent(QMouseEvent* mouseE) override; // 重写鼠标双击事件，实现打开下载路径
};