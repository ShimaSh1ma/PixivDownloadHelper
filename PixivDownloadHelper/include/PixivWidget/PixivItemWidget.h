#pragma once

#include "BasicButton.h"
#include "BasicWidget.h"

/*pixiv下载项目标题窗口， 由若干label组成*/
class PixivDownloadItemTitleWidget final : public TransparentWidget {
  public:
    explicit PixivDownloadItemTitleWidget(const std::string& str);
    ~PixivDownloadItemTitleWidget() = default;

  private:
    TextLabel* urlLabel; // 显示url的标签
    QHBoxLayout* layout; // 水平布局
};

// pixiv下载项目缩略图窗口
class PixivDownloadItemPreviewWidget final : public TransparentWidget {
    Q_OBJECT
  public:
    explicit PixivDownloadItemPreviewWidget();
    ~PixivDownloadItemPreviewWidget() = default;

    PixivDownloadItemPreviewWidget(const PixivDownloadItemPreviewWidget&) = delete;
    PixivDownloadItemPreviewWidget& operator=(const PixivDownloadItemPreviewWidget&) = delete;
    PixivDownloadItemPreviewWidget(PixivDownloadItemPreviewWidget&&) = delete;
    PixivDownloadItemPreviewWidget& operator=(PixivDownloadItemPreviewWidget&&) = delete;
  public slots:
    void loadPreviewImage(const std::string& imagePath); // 加载缩略图
  private:
    QLabel* previewImage; // 缩略图
    QHBoxLayout* layout;  // 水平布局

    std::string previewImagePath = DEFAULT_PREVIEW_PATH; // 缩略图路径
};

// pixiv下载项目下载状态窗口
class PixivDownloadItemStateWidget final : public TransparentWidget {
    Q_OBJECT
  public:
    explicit PixivDownloadItemStateWidget();
    ~PixivDownloadItemStateWidget() = default;

    PixivDownloadItemStateWidget(const PixivDownloadItemStateWidget&) = delete;
    PixivDownloadItemStateWidget& operator=(const PixivDownloadItemStateWidget&) = delete;
    PixivDownloadItemStateWidget(PixivDownloadItemStateWidget&&) = delete;
    PixivDownloadItemStateWidget& operator=(PixivDownloadItemStateWidget&&) = delete;

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
  public slots:
    void setState(const downloadState& _state);             // 设置下载状态
    void setProgress(const int& total, const int& success); // 设置下载进度
};

// pixiv下载项目
class PixivDownloadItem final : public PressWidget {
    Q_OBJECT
  public:
    explicit PixivDownloadItem(const std::string& _url, const std::string& _path, const bool& foldOrUnfold = true);
    ~PixivDownloadItem() = default;

    PixivDownloadItem(const PixivDownloadItem&) = delete;
    PixivDownloadItem& operator=(const PixivDownloadItem&) = delete;
    PixivDownloadItem(PixivDownloadItem&&) = delete;
    PixivDownloadItem& operator=(PixivDownloadItem&&) = delete;

    std::string getUrl();
    std::string getPath();
    void previewWidgetVisiable(bool visiable);
  public slots:
    void checkUrlType(); // 检查url类型
  signals:
    void previewImageSignal(std::string);                // 发射携带预览图路径的信号
    void downloadCompleteSignal();                       // 下载完成时发射此信号
    void downloadProgressSignal(int total, int success); // 下载过程中报告下载进度函数
  private:
    PixivDownloadItemTitleWidget* titleWidget;     // 标题窗口
    PixivDownloadItemPreviewWidget* previewWidget; // 缩略图窗口
    PixivDownloadItemStateWidget* stateWidget;     // 下载状态窗口
    QVBoxLayout* layout;                           // 垂直布局

    void pixivDownload();    // pixiv下载函数
    void telegramDownload(); // telegram下载函数

    std::string downloadUrl;                                          // 下载URL
    const std::string downloadPath;                                   // 下载路径
    virtual void mouseDoubleClickEvent(QMouseEvent* mouseE) override; // 重写鼠标双击事件，实现打开下载路径
};