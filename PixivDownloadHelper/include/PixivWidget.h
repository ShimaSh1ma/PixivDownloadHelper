#pragma once

#include <memory>
#include <regex>
#include <thread>
#include <unordered_set>
#include <vector>

#include <QtCore/qtextcodec.h>
#include <QtGui/qdesktopservices.h>
#include <QtGui/qevent.h>
#include <QtWidgets/qlayout.h>

#include "BasicButton.h"
#include "BasicWidget.h"
#include "publicFunction.h"

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

// pixiv下载项目总览窗口
class PixivDownloadItemWidget final : public TransparentWidget {
    Q_OBJECT
  public:
    explicit PixivDownloadItemWidget(); // 构造函数
    ~PixivDownloadItemWidget() = default;

    PixivDownloadItemWidget(const PixivDownloadItemWidget&) = delete;
    PixivDownloadItemWidget& operator=(const PixivDownloadItemWidget&) = delete;
    PixivDownloadItemWidget(PixivDownloadItemWidget&&) = delete;
    PixivDownloadItemWidget& operator=(PixivDownloadItemWidget&&) = delete;
  public slots:
    void initLoadItem(const std::string& url,
                      const std::string& downloadPath); // 初始化时添加未完成项目
    void addDownloadItem(const std::string& url, const std::string& downloadPath = _downloadPath);
    void checkUrl(const std::string& url);             // 判断url类型，发送不同信号
    void getPixivAllIllustsUrl(const std::string& id); // 获取用户所有作品url
    void getPixivTaggedIllustsUrl(const std::string& id,
                                  const std::string& tag); // 获取用户按标签筛选后作品url

    void startDownload();         // 开始下载
    void checkDownloadingOrNot(); // 检查下载状态
    void downloadCompleted();     // 当前项目下载完毕，还有剩余未下载则downloadingIndex+1

    void caculateColumn(); // 计算当前布局列数
    void adjustLayout();   // 调整网格布局，适应窗口变化

    void foldDownloadItems();   // 折叠所有下载项目
    void unfoldDownloadItems(); // 展开所有下载项目
  signals:
    void itemAddedSignal();     // 有新项目加入时发出信号
    void startDownloadSignal(); // 开始下载信号
    void adjustLayoutSignal();  // 调整布局信号
    void initLoadItemSignal(std::string url, std::string downloadPath);
    void urlIsSingleWorkSignal(std::string url, std::string downloadPath); // 输入url是单个作品url,携带单个作品url
    void urlIsAllWorkSignal(std::string id);                               // 输入url是用户所有作品url，携带用户id
    void urlIsTaggedWorkSignal(std::string id, std::string tag); // 输入url是用户筛选后作品url，携带用户id，筛选标签tag
  private:
    void loadDownloadData(); // 读取上次未下载完成数据

    QGridLayout* Glayout; // 网格布局

    std::list<PixivDownloadItem*> itemList;                        // 储存所有下载项目的向量组
    std::list<PixivDownloadItem*>::const_iterator downloadingItem; // 指向正在下载项目的迭代器

    bool foldOrUnfold = true; // 下载项目是否展开状态位，在槽函数中改变

    bool downloadingOrNot = false; // 表示下载是否在进行中的状态位

    int row = 1;    // 布局行数
    int column = 1; // 布局列数

    std::unordered_set<std::string> hashTable; // 哈希表判断重复
};

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