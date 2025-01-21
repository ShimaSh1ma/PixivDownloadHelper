#include "PixivWidget/PixivItemContainerWidget.h"

#include <fstream>
#include <regex>
#include <thread>

#include <QtCore/qtextcodec.h>

#include <SocketModule/HttpRequest.h>
#include <SocketModule/UrlParser.h>

#include "publicFunction.h"

// PixivItemContainerWidget
PixivItemContainerWidget::PixivItemContainerWidget() : TransparentWidget() {

    // 注册std::string作为信号槽参数
    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<std::vector<std::string>>("std::vector<std::string>");

    // item窗口链表初始化
    itemList = std::list<PixivItemWidget*>();
    // 哈希表初始化
    hashTable = std::unordered_set<std::string>();
    Glayout = new QGridLayout();

    // itemList添加头节点
    itemList.emplace_back(nullptr);

    // 设置聚焦策略
    this->setFocusPolicy(Qt::FocusPolicy::TabFocus);

    // 信号与槽连接
    connect(this, &PixivItemContainerWidget::itemAddedSignal, this,
            &PixivItemContainerWidget::checkDownloadingOrNot); /*有下载项目加入后，检测是否需要唤醒下载队列
                                                              下载正在进行则不唤醒，没有正在下载项目则唤醒*/
    connect(this, &PixivItemContainerWidget::startDownloadSignal, this,
            &PixivItemContainerWidget::startDownload); // 收到开始下载信号，开始下载当前队首项目

    connect(this, &PixivItemContainerWidget::adjustLayoutSignal, this,
            &PixivItemContainerWidget::adjustLayout); // 收到布局行列改变信号，重新布局

    connect(this, &PixivItemContainerWidget::urlIsSingleWorkSignal, this,
            &PixivItemContainerWidget::addDownloadItem); // url是单个作品url，则创建一个下载窗口

    connect(this, &PixivItemContainerWidget::urlIsAllWorkSignal, this,
            &PixivItemContainerWidget::getPixivAllIllustsUrl); // url是用户所有作品url，则发送请求获取每一个作品url

    connect(this, &PixivItemContainerWidget::urlIsTaggedWorkSignal, this,
            &PixivItemContainerWidget::
                getPixivTaggedIllustsUrl); // url是用户筛选后作品url，则发送请求获取筛选后每一个作品url

    connect(this, &PixivItemContainerWidget::initLoadItemSignal, this, &PixivItemContainerWidget::initLoadItem);

    Glayout->setMargin(0);               // 布局周围间距为零
    Glayout->setAlignment(Qt::AlignTop); // 默认上对齐
    this->setLayout(Glayout);

    // 加载未完成下载项目
    loadDownloadData();
}

void PixivItemContainerWidget::initLoadItem(const std::string& url, const std::string& downloadPath) {
    // 添加进链表数组中
    itemList.emplace_back(new PixivItemWidget(url, downloadPath, this->foldOrUnfold));
    // 初始化迭代器
    if (itemList.size() == 2) {
        downloadingItem = itemList.cbegin();
    }

    emit adjustLayoutSignal(); // 刷新布局
    emit itemAddedSignal();    // 发送信号提示有新项目加入
}

void PixivItemContainerWidget::addDownloadItem(const std::string& url, const std::string& downloadPath) {
#if defined(_WIN32)
    // 检查下载路径是否存在，及是否拥有写入权限
    QTextCodec* code = QTextCodec::codecForName("GB2312");
    mkdir(code->fromUnicode(downloadPath.c_str()).data());
#endif
    mkdir(downloadPath);

    // 判断此url下载项目是否已经存在
    if (!hashTable.insert(url).second) {
        return;
    }

    // 添加进链表数组中
    itemList.emplace_back(new PixivItemWidget(url, downloadPath, this->foldOrUnfold));
    // 保存下载信息
    saveDownloadData(url + "\n" + downloadPath);

    // 初始化迭代器
    if (itemList.size() == 2) {
        downloadingItem = itemList.cbegin();
    }

    emit adjustLayoutSignal(); // 刷新布局
    emit itemAddedSignal();    // 发送信号提示有新项目加入
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
    if (std::regex_match(url, re, urlSingleWork) || std::regex_match(url, re, ruleTelegram)) {
        emit urlIsSingleWorkSignal(url, _downloadPath); // 发送信号指示输入是单个作品的url
        return;
    } else if (std::regex_match(url, re, ruleAll)) { // url为用户所有作品
        emit urlIsAllWorkSignal(re[1].str());
        return;
    } else if (std::regex_match(url, re, ruleTags)) { // url为用户筛选后作品
        emit urlIsTaggedWorkSignal(re[1].str(), re[2].str());
        return;
    } else {
        return;
    }
}

void PixivItemContainerWidget::getPixivAllIllustsUrl(const std::string& id) {
    auto lamda = [=]() {
        // ajax接口url
        std::string ajaxUrl = "https://www.pixiv.net/ajax/user/" + id + "/profile/all";

        auto urlP = std::make_unique<UrlParser>();
        urlP->parseUrl(ajaxUrl);
        auto hr = std::make_unique<HttpRequest>();
        hr->setUrl(*urlP);
        hr->addHttpHead({{"cookie", _pixivCookie}});
        std::string* json = new std::string;
        // 请求json
        while (*json == EMPTY_STRING) {
            //*json = M->requestHtml(*urlP, hr->request());
        }

        // json illusts值匹配规则
        std::regex rule("\\{\"illusts\":\\{([^\\}]+)");
        std::smatch re{};
        std::vector<std::string>* url = new std::vector<std::string>; // 存放所有作品url的数组
        // 预申请空间
        url->reserve(200);
        if (std::regex_search(*json, re, rule)) {
            *json = re[1];
            auto begin = json->cbegin();
            auto end = json->cend();
            // 作品id匹配规则
            std::regex insiderule("\"(\\d+)\"");
            // 循环匹配所有作品id
            while (std::regex_search(begin, end, re, insiderule)) {
                // 作品id转换为url
                url->push_back("https://www.pixiv.net/artworks/" + re[1].str());
                // 发送带有url的信号新建下载窗口
                emit urlIsSingleWorkSignal(url->back(), _downloadPath);
                // 更改偏移量，继续匹配
                begin = re[1].second;
            }
        }
        delete url;
        delete json;
        return;
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
            auto hr = std::make_unique<HttpRequest>();
            hr->setUrl(*urlP);
            hr->addHttpHead({{"cookie", _pixivCookie}});
            std::string* json = new std::string;
            // 请求json
            while (*json == EMPTY_STRING) {
                //*json = M->requestHtml(*urlP, hr->request());
            }

            std::smatch re{};
            // 获取匹配作品总数
            if (page == 0) {
                std::regex ruleTotal("\"total\":([\\d]+)");
                if (std::regex_search(*json, re, ruleTotal)) {
                    totalCount = atoi(re[1].str().c_str()); // 作品总数
                    pageCount = totalCount / 48;            // 分页总数
                    restCount = totalCount % 48;            // 最后一页剩余作品数
                }
            }

            // json illusts值匹配规则
            std::regex rule("\"id\":\"([\\d]{8,9})\"");
            std::vector<std::string> url;
            url.reserve(50);

            auto begin = json->cbegin();
            auto end = json->cend();

            while (std::regex_search(begin, end, re, rule)) {
                // 作品id转换为url
                url.push_back("https://www.pixiv.net/artworks/" + re[1].str());

                emit urlIsSingleWorkSignal(url.back(), _downloadPath);
                // 更改偏移量，继续匹配
                begin = re[1].second;
            }
            delete json;
            page++; // 页面数加一
        } while (page < pageCount);

        return;
    };

    std::thread t(lambda);
    t.detach();
}

void PixivItemContainerWidget::startDownload() {
    // 有待下载项目则迭代器迭代
    this->downloadingItem++;
    // 开始下载后绑定正在下载的项目的完成信号和downloadCompleted();
    connect(*downloadingItem, &PixivItemWidget::downloadCompleteSignal, this,
            &PixivItemContainerWidget::downloadCompleted);

    this->downloadingOrNot = true;      // 标记正在下载
    (*downloadingItem)->checkUrlType(); // 开始下载
    return;
}

void PixivItemContainerWidget::checkDownloadingOrNot() {
    if (downloadingOrNot) {
        return;
    }
    if (!downloadingOrNot) {
        emit startDownloadSignal();
        return;
    }
}

void PixivItemContainerWidget::downloadCompleted() {
    // 解绑下载完成项目的downloadCompleteSignal()信号和downloadCompleted()函数
    disconnect(*downloadingItem, &PixivItemWidget::downloadCompleteSignal, this,
               &PixivItemContainerWidget::downloadCompleted);
    // 删除此条下载信息
    deleteDownloadData((*downloadingItem)->getUrl() + "\n" + (*downloadingItem)->getPath());
    // 下载状态：未在下载中，下载队列休眠
    this->downloadingOrNot = false;
    // 没有待下载项目则返回
    if (*this->downloadingItem == this->itemList.back()) {
        this->downloadingOrNot = false;
        return;
    }
    emit startDownloadSignal();
    return;
}

void PixivItemContainerWidget::caculateColumn() {
    // 当前列数对应的窗口长度区间
    int maxLength = (this->column + 1) * PIXIV_DOWNLOAD_ITEM_MIN_WIDTH // 上限
                    + this->column * this->Glayout->spacing();
    int minLength = this->column * PIXIV_DOWNLOAD_ITEM_MIN_WIDTH // 下限
                    + (this->column - 1) * this->Glayout->spacing();

    // 超出区间则更新列数，并发送更新布局的信号
    if (this->width() < minLength || this->width() > maxLength) {
        this->column = this->size().width() / (PIXIV_DOWNLOAD_ITEM_MIN_WIDTH + this->Glayout->spacing());
        if (this->column == 0) {
            this->column = 1;
        }
        emit adjustLayoutSignal();
    }
}

void PixivItemContainerWidget::adjustLayout() {
    // 没有项目则不布局
    if (itemList.size() == 0) {
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
    for (auto it = ++itemList.cbegin(); it != itemList.cend(); ++it) {
        if (_column < this->column) {
            this->Glayout->addWidget(*it, _row, _column, Qt::AlignTop);
            _column++;
        } else {
            _column = 0;
            _row++;
            this->Glayout->addWidget(*it, _row, _column, Qt::AlignTop);
            _column++;
        }
    }
    // 调整窗口大小，适应布局变化
    this->row = ++_row;
    this->setMinimumHeight(row * (PIXIV_DOWNLOAD_ITEM_WITH_PIC_HEIGHT * (int)foldOrUnfold +
                                  PIXIV_DOWNLOAD_ITEM_WITHOUT_PIC_HEIGHT * (int)!foldOrUnfold) +
                           (row - 1) * this->Glayout->spacing());
    this->setLayout(Glayout);
    this->resize(sizeHint()); // 强制刷新，防止布局错误
}

void PixivItemContainerWidget::foldDownloadItems() {
    for (auto it = ++this->itemList.cbegin(); it != this->itemList.cend(); ++it) {
        (*it)->previewWidgetVisiable(false);
        this->foldOrUnfold = false;
        (*it)->setFixedHeight(PIXIV_DOWNLOAD_ITEM_WITHOUT_PIC_HEIGHT);
    }
    emit adjustLayoutSignal();
    return;
}

void PixivItemContainerWidget::unfoldDownloadItems() {
    for (auto it = ++this->itemList.cbegin(); it != this->itemList.cend(); ++it) {
        (*it)->previewWidgetVisiable(true);
        this->foldOrUnfold = true;
        (*it)->setFixedHeight(PIXIV_DOWNLOAD_ITEM_WITH_PIC_HEIGHT);
    }
    emit adjustLayoutSignal();
    return;
}

void PixivItemContainerWidget::loadDownloadData() {
    auto f = [=]() {
        std::ifstream i(CONFIG_UNDONE_PATH);
        std::string buf;
        std::string url;
        std::string path;
        if (i.is_open()) {
            while (std::getline(i, buf)) {
                url = buf;
                std::getline(i, buf);
                path = buf;
                emit initLoadItemSignal(url, path);
            }
            i.close();
        }

        emit adjustLayoutSignal(); // 刷新布局
        return;
    };

    std::thread th(f);
    th.detach();
    return;
}