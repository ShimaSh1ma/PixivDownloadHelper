#include "PixivWidget/PixivItemContainerWidget.h"

#include <fstream>
#include <regex>
#include <shared_mutex>
#include <thread>

#include <QtCore/qtextcodec.h>

#include <SocketModule/ClientSocket.h>
#include <SocketModule/HttpRequest.h>
#include <SocketModule/HttpResponseParser.h>
#include <SocketModule/UrlParser.h>

#include "publicFunction.h"

constexpr uint8_t MAX_ACTIVE_COUNTS = 3;
// 下载项目数组共享锁
std::shared_mutex vectorMutex;

// PixivItemContainerWidget
PixivItemContainerWidget::PixivItemContainerWidget() : TransparentWidget() {

    // 注册std::string作为信号槽参数
    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<std::vector<std::string>>("std::vector<std::string>");

    // item窗口数组初始化
    itemArray = std::vector<PixivItemWidget*>();
    itemArray.reserve(100);
    // 哈希表初始化
    hashTable = std::unordered_set<std::string>();
    Glayout = new QGridLayout();

    // 设置聚焦策略
    this->setFocusPolicy(Qt::FocusPolicy::TabFocus);

    Glayout->setMargin(0);               // 布局周围间距为零
    Glayout->setAlignment(Qt::AlignTop); // 默认上对齐
    this->setLayout(Glayout);

    // 加载未完成下载项目
    loadDownloadData();
}

void PixivItemContainerWidget::addDownloadItem(const std::string& url, const std::string& downloadPath) {
    // 判断此url下载项目是否已经存在
    if (!hashTable.insert(url).second) {
        return;
    }

    std::unique_lock<std::shared_mutex> uniquelock(vectorMutex);
    // 添加进链表数组中
    itemArray.emplace_back(new PixivItemWidget(url, downloadPath, this->foldOrUnfold));
    uniquelock.unlock();
    // 保存下载信息
    saveDownloadData(url + "\n" + downloadPath);

    this->adjustLayout();  // 刷新布局
    this->startDownload(); // 检查是否正在下载
}

void PixivItemContainerWidget::checkUrl(const std::string& url) { // 判断url格式
    // 单个作品url
    std::regex urlSingleWork(REGEX_PIXIV_ARTWORK);
    std::regex ruleTelegram(REGEX_TELEGRAM);
    // 用户所有作品url的匹配规则
    std::regex ruleAll(REGEX_PIXIV_USER_ALL);
    // 用户按照tag筛选后的url匹配规则
    std::regex ruleTags(REGEX_PIXIV_USER_TAGGED);
    std::smatch re;
    // url格式正确则创建下载项目
    if (std::regex_match(url, re, urlSingleWork) || std::regex_match(url, re, ruleTelegram)) { // 单个作品的url
        addDownloadItem(url, _downloadPath);
    } else if (std::regex_match(url, re, ruleAll)) { // url为用户所有作品
        getPixivAllIllustsUrl(re[1].str());
    } else if (std::regex_match(url, re, ruleTags)) { // url为用户筛选后作品
        getPixivTaggedIllustsUrl(re[1].str(), re[2].str());
    }
}

void PixivItemContainerWidget::getPixivAllIllustsUrl(const std::string& id) {
    auto lamda = [=]() {
        // ajax接口url
        std::string ajaxUrl = "https://www.pixiv.net/ajax/user/" + id + "/profile/all";

        auto urlP = std::make_unique<UrlParser>();
        urlP->parseUrl(ajaxUrl);

        auto httpRequest = std::make_unique<HttpRequest>();
        httpRequest->setUrl(*urlP);
        httpRequest->addHttpHead({{"cookie", _pixivCookie}});

        std::string json;
        std::string respCode;
        int sIndex = -1;

        while (respCode != "200") {
            if (sIndex == -1) {
                sIndex = ClientSocket::connectToServer(urlP->host, "443");
                if (sIndex != -1) {
                    if (ClientSocket::socketSend(sIndex, httpRequest->httpRequest())) {
                        std::unique_ptr<HttpResponseParser> resp = ClientSocket::socketReceive(sIndex);
                        if (resp == nullptr) {
                            continue;
                        }
                        respCode = resp->getStatusCode();
                        if (respCode == "200") {
                            json = resp->getPayload();
                        }
                    }
                }
            }
            ClientSocket::releaseSocket(sIndex);
        }

        // json illusts值匹配规则
        std::regex rule("\\{\"illusts\":\\{([^\\}]+)");
        std::smatch re{};
        std::vector<std::string> urlV; // 存放所有作品url的数组
        // 预申请空间
        urlV.reserve(200);
        if (std::regex_search(json, re, rule)) {
            json = re[1];
            auto begin = json.cbegin();
            auto end = json.cend();
            // 作品id匹配规则
            std::regex insiderule("\"(\\d+)\"");
            // 循环匹配所有作品id
            while (std::regex_search(begin, end, re, insiderule)) {
                // 作品id转换为url
                urlV.push_back("https://www.pixiv.net/artworks/" + re[1].str());
                // 发送带有url的信号新建下载窗口
                addDownloadItem(urlV.back(), _downloadPath);
                // 更改偏移量，继续匹配
                begin = re[1].second;
            }
        }
    };

    std::thread t(lamda);
    t.detach();
}

void PixivItemContainerWidget::getPixivTaggedIllustsUrl(const std::string& id, const std::string& tag) {
    auto lambda = [=]() {
        int page{0};       // 当前页数
        int totalCount{0}; // 筛选后图片总数
        int pageCount{0};  // 总页数
        int restCount{0};  // 最后一页作品数量

        do {
            // ajax接口url
            std::string ajaxUrl = "https://www.pixiv.net/ajax/user/" + id + "/illustmanga/tag?tag=" + tag +
                                  "&offset=" + std::to_string(page * 48) + "&limit=48&lang=zh";

            auto urlP = std::make_unique<UrlParser>();
            urlP->parseUrl(ajaxUrl);

            auto httpRequest = std::make_unique<HttpRequest>();
            httpRequest->setUrl(*urlP);
            httpRequest->addHttpHead({{"cookie", _pixivCookie}});

            std::string json;
            std::string respCode;
            int sIndex = -1;

            while (respCode != "200") {
                if (sIndex == -1) {
                    sIndex = ClientSocket::connectToServer(urlP->host, "443");
                    if (sIndex != -1) {
                        if (ClientSocket::socketSend(sIndex, httpRequest->httpRequest())) {
                            std::unique_ptr<HttpResponseParser> resp = ClientSocket::socketReceive(sIndex);
                            if (resp == nullptr) {
                                continue;
                            }
                            respCode = resp->getStatusCode();
                            if (respCode == "200") {
                                json = resp->getPayload();
                            }
                        }
                    }
                }
                ClientSocket::releaseSocket(sIndex);
            }

            std::smatch re{};
            // 获取匹配作品总数
            if (page == 0) {
                std::regex ruleTotal("\"total\":([\\d]+)");
                if (std::regex_search(json, re, ruleTotal)) {
                    totalCount = atoi(re[1].str().c_str()); // 作品总数
                    pageCount = totalCount / 48;            // 分页总数
                    restCount = totalCount % 48;            // 最后一页剩余作品数
                }
            }

            // json illusts值匹配规则
            std::regex rule("\"id\":\"([\\d]{8,9})\"");
            std::vector<std::string> url;
            url.reserve(50);

            auto begin = json.cbegin();
            auto end = json.cend();

            while (std::regex_search(begin, end, re, rule)) {
                // 作品id转换为url
                url.push_back("https://www.pixiv.net/artworks/" + re[1].str());
                addDownloadItem(url.back(), _downloadPath);
                // 更改偏移量，继续匹配
                begin = re[1].second;
            }
            page++; // 页面数加一
        } while (page < pageCount);
    };

    std::thread t(lambda);
    t.detach();
}

void PixivItemContainerWidget::startDownload() {
    while (activeItemCounts.load() < MAX_ACTIVE_COUNTS) {
        std::uint64_t expectValue = lastActiveItemIndex.load();
        if (expectValue >= itemArray.size() - 1) {
            return;
        }
        if (lastActiveItemIndex.compare_exchange_weak(expectValue, expectValue + 1)) {
            std::shared_lock<std::shared_mutex> sharedlock(vectorMutex);
            PixivItemWidget& activeItem = *itemArray[expectValue];
            sharedlock.unlock();

            activeItemCounts.fetch_add(1);
            // 完成下载后的回调
            std::function completeFunction = [this](const std::string& url, const std::string& path) {
                // 删除此条下载信息
                deleteDownloadData(url + "\n" + path);
                // 正在下载数减1
                activeItemCounts.fetch_sub(1);
                // 继续唤起下载
                startDownload();
            };
            activeItem.completeFunction = completeFunction;
            activeItem.checkUrlType(); // 开始下载
        }
    }
}

void PixivItemContainerWidget::caculateColumn() {
    // 当前列数对应的窗口长度区间
    int maxLength = (this->column + 1) * PIXIV_DOWNLOAD_ITEM_MIN_WIDTH // 上限
                    + this->column * this->Glayout->spacing();
    int minLength = this->column * PIXIV_DOWNLOAD_ITEM_MIN_WIDTH // 下限
                    + (this->column - 1) * this->Glayout->spacing();

    // 超出区间则更新列数
    if (this->width() < minLength || this->width() > maxLength) {
        this->column = this->size().width() / (PIXIV_DOWNLOAD_ITEM_MIN_WIDTH + this->Glayout->spacing());
        if (this->column == 0) {
            this->column = 1;
        }
        adjustLayout();
    }
}

void PixivItemContainerWidget::adjustLayout() {
    // 没有项目则不布局
    if (itemArray.empty()) {
        return;
    }
    // 删除原有布局
    delete Glayout;
    // 新建布局
    Glayout = new QGridLayout();
    Glayout->setMargin(0);               // 布局周围间距为零
    Glayout->setSpacing(5);              // 设置间距
    Glayout->setAlignment(Qt::AlignTop); // 默认上对齐

    // 重排布局
    int _row = 0, _column = 0;
    std::shared_lock<std::shared_mutex> sharedlock(vectorMutex);
    for (auto it : itemArray) {
        if (_column < this->column) {
            this->Glayout->addWidget(it, _row, _column, Qt::AlignTop);
            _column++;
        } else {
            _column = 0;
            _row++;
            this->Glayout->addWidget(it, _row, _column, Qt::AlignTop);
            _column++;
        }
    }
    sharedlock.unlock();
    // 调整窗口大小，适应布局变化
    this->row = ++_row;
    this->setMinimumHeight(row * (PIXIV_DOWNLOAD_ITEM_WITH_PIC_HEIGHT * (int)foldOrUnfold +
                                  PIXIV_DOWNLOAD_ITEM_WITHOUT_PIC_HEIGHT * (int)!foldOrUnfold) +
                           (row - 1) * this->Glayout->spacing());
    this->setLayout(Glayout);
    this->resize(sizeHint()); // 强制刷新，防止布局错误
}

void PixivItemContainerWidget::foldDownloadItems() {
    std::shared_lock<std::shared_mutex> sharedlock(vectorMutex);
    for (auto it : itemArray) {
        it->previewWidgetVisiable(false);
        this->foldOrUnfold = false;
        it->setFixedHeight(PIXIV_DOWNLOAD_ITEM_WITHOUT_PIC_HEIGHT);
    }
    adjustLayout();
}

void PixivItemContainerWidget::unfoldDownloadItems() {
    std::shared_lock<std::shared_mutex> sharedlock(vectorMutex);
    for (auto it : itemArray) {
        it->previewWidgetVisiable(true);
        this->foldOrUnfold = true;
        it->setFixedHeight(PIXIV_DOWNLOAD_ITEM_WITH_PIC_HEIGHT);
    }
    adjustLayout();
}

void PixivItemContainerWidget::loadDownloadData() {
    auto f = [this]() {
        std::ifstream i(CONFIG_UNDONE_PATH);
        std::string buf;
        std::string url;
        std::string path;
        if (i.is_open()) {
            while (std::getline(i, buf)) {
                url = buf;
                std::getline(i, buf);
                path = buf;
                this->addDownloadItem(url, path);
            }
            i.close();
        }
    };

    std::thread th(f);
    th.detach();
}