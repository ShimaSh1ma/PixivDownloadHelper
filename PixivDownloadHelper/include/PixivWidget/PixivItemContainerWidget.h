#pragma once

#include <unordered_set>

#include "PixivItemWidget.h"

// pixiv下载项目总览窗口
class PixivItemContainerWidget final : public TransparentWidget {
    Q_OBJECT
  public:
    explicit PixivItemContainerWidget(); // 构造函数
    ~PixivItemContainerWidget() = default;

    PixivItemContainerWidget(const PixivItemContainerWidget&) = delete;
    PixivItemContainerWidget& operator=(const PixivItemContainerWidget&) = delete;
    PixivItemContainerWidget(PixivItemContainerWidget&&) = delete;
    PixivItemContainerWidget& operator=(PixivItemContainerWidget&&) = delete;
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

    std::list<PixivItemWidget*> itemList;                        // 储存所有下载项目的向量组
    std::list<PixivItemWidget*>::const_iterator downloadingItem; // 指向正在下载项目的迭代器

    bool foldOrUnfold = true; // 下载项目是否展开状态位，在槽函数中改变

    bool downloadingOrNot = false; // 表示下载是否在进行中的状态位

    int row = 1;    // 布局行数
    int column = 1; // 布局列数

    std::unordered_set<std::string> hashTable; // 哈希表判断重复
};