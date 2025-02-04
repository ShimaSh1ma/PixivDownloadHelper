#pragma once

#include <atomic>
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

  public:
    void checkUrl(const std::string& url); // 判断url类型，发送不同信号

    void caculateColumn(); // 计算当前布局列数
    void adjustLayout();   // 调整网格布局，适应窗口变化

    void foldDownloadItems();   // 折叠所有下载项目
    void unfoldDownloadItems(); // 展开所有下载项目

signals:
    void addItemSignal(std::string url,std::string path);
  private:
    void startDownload();                              // 开始下载
    void getPixivAllIllustsUrl(const std::string& id); // 获取用户所有作品url
    void getPixivTaggedIllustsUrl(const std::string& id,
                                  const std::string& tag); // 获取用户按标签筛选后作品url
    void addDownloadItem(const std::string& url, const std::string& downloadPath = _downloadPath); // 添加下载项目
    void loadDownloadData(); // 读取上次未下载完成数据

    QGridLayout* Glayout; // 网格布局

    // 储存所有下载项目的向量组
    std::vector<PixivItemWidget*> itemArray;
    // 下载项目是否展开状态位
    bool foldOrUnfold = true;
    // 记录当前最后一个正在下载项目的索引
    std::atomic_uint64_t lastActiveItemIndex = 0;
    // 标记当前正在下载的个数，用于并行下载控制
    std::atomic_uint8_t activeItemCounts = 0;

    int row = 1;    // 布局行数
    int column = 1; // 布局列数

    std::unordered_set<std::string> hashTable; // 哈希表判断重复
};