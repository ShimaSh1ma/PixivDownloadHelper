#ifndef _PixivWidget
#define _PixivWidget

#include <vector>
#include <regex>
#include <thread>

#include <QtWidgets/qlayout.h>
#include <QtCore/qtextcodec.h>
#include <QtGui/qevent.h>
#include <QtGui/qdesktopservices.h>

#include "DownloadMode/Crawler.h"
#include "DownloadMode/publicFunction.h"
#include "BasicWidget.h"
#include "BasicButton.h"
class PixivUrlInputWidget ://输入url的窗口
    public TranslucentWidget    /*含有一个文本框和下载按钮*/
{
public:
    QHBoxLayout* layout;//水平布局

    PixivUrlEdit* edit;//文本框
    ToolButton* dButton;//下载按钮

    explicit PixivUrlInputWidget();//构造
    ~PixivUrlInputWidget();
private:
};

class PixivDownloadItemTitleWidget :/*pixiv下载项目标题窗口，
                                    由若干label组成*/
    public TransparentWidget
{
public:
    textLabel* urlLabel;//显示url的标签

    QHBoxLayout* layout;//水平布局

    explicit PixivDownloadItemTitleWidget(const std::string& str);
    ~PixivDownloadItemTitleWidget();

    std::string getDownloadUrl();//返回下载url
private:
    std::string downloadUrl{};//目标下载url
};

class PixivDownloadItemPreviewWidget ://pixiv下载项目缩略图窗口
    public TransparentWidget
{
    Q_OBJECT
public:
    QLabel* previewImage;//缩略图

    QHBoxLayout* layout;//水平布局

    explicit PixivDownloadItemPreviewWidget();
    ~PixivDownloadItemPreviewWidget();
public slots:
    void loadPreviewImage(const std::string& imagePath);//加载缩略图
private:
    std::string previewImagePath{ _default_preview_path };//缩略图路径
};

class PixivDownloadItemStateWidget ://pixiv下载项目下载状态窗口
    public TransparentWidget
{
    Q_OBJECT
public:
    textLabel* downloadStateLabel;//显示下载状态的标签
    textLabel* totalCountLabel;//显示总图片数的标签
    textLabel* separatorLabel;//显示分隔符
    textLabel* successCountLabel;//显示下载成功图片数的标签

    QHBoxLayout* layout;//水平布局

    explicit PixivDownloadItemStateWidget();
    ~PixivDownloadItemStateWidget();
private:
    int imageCount{ 0 };//总图片数
    int successCount{ 0 };//下载成功数

    downloadState state = { downloadState::WAITING };//默认为等待状态
    QString downloadStateString();//根据状态枚举量返回下载状态字符串
public slots:
    void setState(const downloadState& _state);   //设置下载状态
    void setProgress(const int& total, const int& success);//设置下载进度
};

class PixivDownloadItem ://pixiv下载项目
    public TranslucentWidget
{
    Q_OBJECT
public:
    PixivDownloadItemTitleWidget* titleWidget;//标题窗口
    PixivDownloadItemPreviewWidget* previewWidget;//缩略图窗口
    PixivDownloadItemStateWidget* stateWidget;//下载状态窗口
    QVBoxLayout* layout;//垂直布局

    explicit  PixivDownloadItem(const std::string& _url,
        const std::string& _path,
        const bool& foldOrUnfold = true);
    ~PixivDownloadItem();

public slots:
    void pixivDownload();//pixiv下载函数
signals:
    void previewImageSignal(std::string);//发射携带预览图路径的信号
    void downloadCompleteSignal();//下载完成时发射此信号
    void downloadProgressSignal(int total, int success);//下载过程中报告下载进度函数
private:
    const std::string downloadPath{};//下载路径

    virtual void mouseDoubleClickEvent(QMouseEvent* mouseE);//重写鼠标点击事件，实现预览图显示或隐藏
};

class PixivDownloadTopWidget :  /*Pixiv下载窗口上方功能窗口，提供控制展开或折叠下载项目缩略图功能*/
    public TransparentWidget
{
public:
    ToolButton* foldButton;     //折叠按钮，按下隐藏下载缩略图
    ToolButton* unfoldButton;   //展开按钮，按下显示下载缩略图

    QHBoxLayout* layout;//水平布局

    PixivDownloadTopWidget();
    ~PixivDownloadTopWidget();
private:
};

class PixivDownloadItemWidget ://pixiv下载项目总览窗口
    public TransparentWidget
{
    Q_OBJECT
public slots:
    void addDownloadItem(const std::string& url);/*按下download按键，判断url是否有效，
                                             有效则添加下载项目, 并发出itemAdded（）信号*/
    void checkUrl(const std::string& url);//判断url类型，发送不同信号
    void getPixivAllIllustsUrl(const std::string& id);//获取用户所有作品url
    void getPixivTaggedIllustsUrl(const std::string& id, const std::string& tag);//获取用户按标签筛选后作品url

    void startDownload();//开始下载
    void checkDownloadingOrNot();//检查下载状态
    void downloadCompleted();//当前项目下载完毕，还有剩余未下载则downloadingIndex+1

    void caculateColumn();//计算当前布局列数
    void adjustLayout();//调整网格布局，适应窗口变化

    void foldDownloadItems();//折叠所有下载项目
    void unfoldDownloadItems();//展开所有下载项目
signals:
    void itemAddedSignal();//有新项目加入时发出信号
    void downloadStartSignal();//开始下载信号
    void refreshLayoutSignal();//刷新布局信号
    void urlIsSingleWorkSignal(std::string url);//输入url是单个作品url,携带单个作品url
    void urlIsAllWorkSignal(std::string id);//输入url是用户所有作品url，携带用户id
    void urlIsTaggedWorkSignal(std::string id, std::string tag);//输入url是用户筛选后作品url，携带用户id，筛选标签tag
public:
    QGridLayout* Glayout;//网格布局

    explicit PixivDownloadItemWidget();//构造函数
    ~PixivDownloadItemWidget();
private:
    std::vector<PixivDownloadItem*>* itemVector;//储存所有下载项目的向量组

    bool foldOrUnfold{ true };//下载项目是否展开状态位，在槽函数中改变

    bool downloadingOrNot{ false };//表示下载是否在进行中的状态位
    int downloadingIndex{ 0 };//当前下载项目索引序号
    int itemCount{ 0 };//下载项目总数

    int column{ 1 };//布局列数
};

class PixivDownloadWidget ://用scrollarea提供滚动条显示PixivDownloadItemWidget
    public TransparentWidget 
{
    Q_OBJECT
public:
    //pixiv下载上方窗口
    PixivDownloadTopWidget* topWidget;
    //pixiv下载项目总览窗口
    PixivDownloadItemWidget* itemWidget;
    //作为容器提供滚动条
    TransparentScrollArea* scrollArea;

    //加入布局自适应窗口大小
    QVBoxLayout* layout;

    explicit PixivDownloadWidget();
    ~PixivDownloadWidget();
signals:
    void sizeChangedSignal();
private:
    void virtual resizeEvent(QResizeEvent* ev);
};

class PixivWidget ://pixiv下载界面
    public TransparentWidget
{
public:
    //垂直布局
    QVBoxLayout* layout;

    //包含的窗口
    PixivUrlInputWidget* uWidget;
    PixivDownloadWidget* dWidget;

    explicit PixivWidget();
    ~PixivWidget();
private:
};

#endif