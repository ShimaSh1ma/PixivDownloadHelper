#include "PixivWidget.h"

#include "GuiConstant.h"
#include "fstream"
#include <SocketModule/ClientSocket.h>
#include <SocketModule/HttpRequest.h>
#include <SocketModule/HttpResponseParser.h>
#include <SocketModule/UrlParser.h>

#include <QtCore/qtextcodec.h>

#include <memory>

// PixivUrlInputWidget
PixivUrlInputWidget::PixivUrlInputWidget() : TranslucentWidget() {
    setMinimumSize(PIXIV_URL_WIDGET_SIZE);
    setMaximumHeight(PIXIV_URL_WIDGET_SIZE.height());

    // 初始化布局
    layout = new QHBoxLayout();

    // 初始化控件
    textEdit = new PixivUrlEdit();
    downloadButton = new AnimationButton("Download", nullptr, PIXIV_DOWNLOAD_BUTTON_SIZE);

    // 设置按钮大小
    downloadButton->setFixedSize(PIXIV_DOWNLOAD_BUTTON_SIZE);

    // 信号与槽连接
    connect(textEdit, &PixivUrlEdit::returnPressed, downloadButton,
            &AnimationButton::click); // 文本框按下回车触发下载按钮点击效果

    connect(downloadButton, &QPushButton::clicked, this, [this]() {
        emit inputUrlSignal(this->textEdit->text().toStdString());
    }); // 按下下载按钮，文本框发送携带文本内容的Text信号

    // 控件加入布局
    layout->setContentsMargins(MARGIN_WIDTH, MARGIN_WIDTH / 2, MARGIN_WIDTH, MARGIN_WIDTH / 2);
    layout->addWidget(textEdit);
    layout->addSpacing(MARGIN_WIDTH / 2);
    layout->addWidget(downloadButton);
    layout->setAlignment(Qt::AlignVCenter);

    // 应用布局
    this->setLayout(layout);
}

// PixivDownloadItemTitleWidget
PixivDownloadItemTitleWidget::PixivDownloadItemTitleWidget(const std::string& url) {
    // 大小设置
    setFixedHeight(PIXIV_DOWNLOAD_TITLE_WIDGET_HEIGHT);

    // 组件初始化
    urlLabel = new TextLabel();
    layout = new QHBoxLayout();
    // url显示标签设置
    urlLabel->setText(url.c_str());
    urlLabel->setMinimumWidth(200);
    urlLabel->setAlignment(Qt::AlignCenter); // 居中显示
    // 布局设置
    layout->addWidget(urlLabel);

    layout->setMargin(0);
    this->setLayout(layout);
}

// PixivDownloadItemPreviewWidget
PixivDownloadItemPreviewWidget::PixivDownloadItemPreviewWidget() {
    // 组件初始化
    previewImage = new QLabel();
    layout = new QHBoxLayout();

    // 设置缩略图
    previewImage->setFixedSize(PIXIV_PREVIEW_SIZE); // 设置最小大小
    QPixmap pix(DEFAULT_PREVIEW_PATH);              // 加载默认预览图
    previewImage->setPixmap(
        pix.scaled(previewImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)); // 缩放预览图适应窗口大小
    previewImage->setAlignment(Qt::AlignCenter);                                          // 居中显示

    // 布局设置
    layout->addWidget(previewImage);
    layout->setMargin(0);

    this->setLayout(layout);
}

void PixivDownloadItemPreviewWidget::loadPreviewImage(const std::string& imagePath) {
    // 保存缩略图路径
    this->previewImagePath = imagePath;

    auto f = [&]() {
        QPixmap* pix = new QPixmap(this->previewImagePath.c_str()); // 加载缩略图
        previewImage->setPixmap(
            pix->scaled(previewImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)); // 缩放缩略图适应窗口大小
        delete pix;
    };

    std::thread thd(f);
    thd.detach();
    return;
}

// PixivDownloadItemStateWidget
PixivDownloadItemStateWidget::PixivDownloadItemStateWidget() {
    // 注册下载状态枚举量
    qRegisterMetaType<downloadState>("downloadState");
    // 大小设置
    setFixedHeight(PIXIV_DOWNLOAD_STATE_HEIGHT);
    // 组件初始化
    totalCountLabel = new TextLabel();
    successCountLabel = new TextLabel();
    separatorLabel = new TextLabel();
    downloadStateLabel = new TextLabel();
    layout = new QHBoxLayout();
    // 数量显示标签设置
    successCountLabel->setFixedSize(80, 20);
    separatorLabel->setFixedSize(10, 20);
    totalCountLabel->setFixedSize(60, 20);

    successCountLabel->setAlignment(Qt::AlignCenter); // 居中显示
    separatorLabel->setAlignment(Qt::AlignCenter);
    totalCountLabel->setAlignment(Qt::AlignCenter);

    successCountLabel->setText(QString::number(successCount) + "(succeed)");
    separatorLabel->setText("/");
    totalCountLabel->setText(QString::number(imageCount) + "(total)");

    // 下载状态显示标签设置
    downloadStateLabel->setText(tr("Waiting"));
    downloadStateLabel->setFixedSize(120, 20);
    downloadStateLabel->setAlignment(Qt::AlignCenter);
    // 布局管理
    layout->addStretch(1);
    layout->addWidget(successCountLabel);
    layout->addWidget(separatorLabel);
    layout->addWidget(totalCountLabel);
    layout->addWidget(downloadStateLabel);
    layout->addStretch(1);
    layout->setMargin(0);

    this->setLayout(layout);
}

void PixivDownloadItemStateWidget::setState(const downloadState& _state) {
    this->state = _state;              // 更改下载状态
    this->downloadStateLabel->setText( // 更新下载状态显示
        tr(downloadStateString().toStdString().c_str()));
}

void PixivDownloadItemStateWidget::setProgress(const int& total, const int& success) {
    this->imageCount = total;
    this->successCount = success;
    // 图片数量标签设置
    successCountLabel->setText(QString::number(successCount) + "(succeed)");
    totalCountLabel->setText(QString::number(imageCount) + "(total)");
}

QString PixivDownloadItemStateWidget::downloadStateString() {
    if (this->state == downloadState::DOWNLOADING) {
        return "Downloading";
    } else if (this->state == downloadState::WAITING) {
        return "Waiting";
    } else if (this->state == downloadState::SUCCESS) {
        return "Succeed";
    } else if (this->state == downloadState::HTTPREQUESTFAILED) {
        return "HttpRequestFailed";
    } else {
        return "";
    }
}

// PixivDownloadItem
PixivDownloadItem::PixivDownloadItem(const std::string& _url, const std::string& _path, const bool& foldOrUnfold)
    : downloadPath(_path) {
    qRegisterMetaType<std::string>("std::string"); // 注册std::string作为信号槽参数
    // 保存下载URL
    downloadUrl = _url;

    // 大小限定
    setFixedHeight(PIXIV_DOWNLOAD_ITEM_WITH_PIC_HEIGHT * (int)foldOrUnfold +
                   PIXIV_DOWNLOAD_ITEM_WITHOUT_PIC_HEIGHT * (int)!foldOrUnfold);
    setMaximumWidth(PIXIV_DOWNLOAD_ITEM_MAX_WIDTH);
    setMinimumWidth(PIXIV_DOWNLOAD_ITEM_MIN_WIDTH);

    // 组件初始化
    titleWidget = new PixivDownloadItemTitleWidget(_url);
    previewWidget = new PixivDownloadItemPreviewWidget();
    stateWidget = new PixivDownloadItemStateWidget();
    layout = new QVBoxLayout();

    // 设置preview窗口折叠或者展开
    previewWidget->setVisible(foldOrUnfold);

    // 信号与槽连接
    connect(this, &PixivDownloadItem::downloadProgressSignal, this->stateWidget,
            &PixivDownloadItemStateWidget::setProgress); // 接收下载进度变化并刷新显示

    connect(this, &PixivDownloadItem::previewImageSignal, this->previewWidget,
            &PixivDownloadItemPreviewWidget::loadPreviewImage); // 收到缩略图路径信号，更新缩略图

    // 布局管理
    layout->addWidget(titleWidget);
    layout->addStretch(1);
    layout->addWidget(previewWidget);
    layout->addStretch(1);
    layout->addWidget(stateWidget);
    layout->setMargin(MARGIN_WIDTH);

    this->setLayout(layout);
}

std::string PixivDownloadItem::getUrl() {
    return downloadUrl;
}

std::string PixivDownloadItem::getPath() {
    return downloadPath;
}

void PixivDownloadItem::previewWidgetVisiable(bool visiable) {
    previewWidget->setVisible(visiable);
}

void PixivDownloadItem::mouseDoubleClickEvent(QMouseEvent* mouseE) {
    if (mouseE->button() == Qt::LeftButton) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(this->downloadPath.c_str()));
        return;
    }
    return;
}

void PixivDownloadItem::checkUrlType() {
    std::regex ruleTelegram(REGEX_TELEGRAM);
    std::smatch re;
    std::string url = downloadUrl;
    if (std::regex_match(url, re, ruleTelegram)) {
        this->telegramDownload();
        return;
    } else {
        this->pixivDownload();
        return;
    }
}

void PixivDownloadItem::pixivDownload() {
    // 将下载状态置为下载中
    this->stateWidget->setState(downloadState::DOWNLOADING);
    std::string url = downloadUrl;
    std::string path = downloadPath;

    // lambd表达式作为子线程运行
    auto f = [=]() {
        std::string refer = url; // 原url作为refer
        std::string ajaxurl;     // pixiv ajax接口url生成
        ajaxurl = pixivAjaxurl(url);
        if (ajaxurl == "") {
            return;
        }

        auto urlP = std::make_unique<UrlParser>();
        urlP->parseUrl(ajaxurl);

        // 组装请求json文件报文
        auto jsonHttpRequest = std::make_unique<HttpRequest>();
        jsonHttpRequest->setUrl(*urlP);
        jsonHttpRequest->addHttpHead({{"referer", refer}, {"Accept-Charset", ""}, {"Cookie", _pixivCookie}});
        // 请求json文件
        std::string json;
        std::string respCode;
        // http请求失败
        while (respCode != "200") {
            static int SFD = -1;
            if (SFD == -1) {
                SFD = ClientSocket::connectToServer(urlP->host, "443");
                static bool flag = true;
                if (flag) {
                    // 更改状态为http请求失败
                    this->stateWidget->setState(downloadState::HTTPREQUESTFAILED);
                    flag = false;
                }
                if (SFD != -1) {
                    if (ClientSocket::socketSend(SFD, jsonHttpRequest->httpRequest())) {
                        std::unique_ptr<HttpResponseParser> resp = ClientSocket::socketReceive(SFD);
                        respCode = resp->getStatusCode();
                        if (respCode == "200") {
                            json = resp->getPayload();
                        }
                    }
                }
            }
            ClientSocket::disconnectToServer(SFD);
        }
        // 更改状态为下载中
        this->stateWidget->setState(downloadState::DOWNLOADING);
        // 去除json文件中的转义字符
        jsonParse(json);
        // 提取图片url,存放url进向量数组
        std::vector<std::string> Vurl = parserHtml(json, REGEX_PIXIV_ILLUST);
        int total = Vurl.size();
        int success = 0;                             // 下载成功个数
        emit downloadProgressSignal(total, success); // 发送信号使下载窗口更新显示

        std::vector<std::string>::iterator it = Vurl.begin();

        UrlParser imageUrl;

        // 创建http请求报文类
        HttpRequest imageHttpRequest;
        imageHttpRequest.addHttpHead({{"referer", refer}, {"accept", "image/*"}, {"cookie", _pixivCookie}});

        // 图片文件路径
        std::string filePath;
        socketIndex socketIdx = -1;

        while (it != Vurl.end()) {
            // 解析图片url
            imageUrl.parseUrl(*it);
            // 连接服务器
            while (socketIdx == -1) {
                socketIdx = ClientSocket::connectToServer(imageUrl.host, "443");
            }
            while (it != Vurl.end()) {
                // 解析图片url
                imageUrl.parseUrl(*it);
                // 组装对应url请求报文
                imageHttpRequest.setUrl(imageUrl);
#if defined(_WIN32)
                // 文件路径utf-8转GB2312，确保正确打开中文路径文件
                QTextCodec* code = QTextCodec::codecForName("GB2312");
                filePath = code->fromUnicode((path + "/" + imageUrl.fileName + imageUrl.fileExtension).c_str());
#elif defined(__APPLE__)
                filePath = path + "/" + imageUrl.fileName;
#endif
                if (socketIdx == -1) {
                    break;
                }
                if (ClientSocket::socketSend(socketIdx, imageHttpRequest.httpRequest())) {
                    std::string data = ClientSocket::socketReceive(socketIdx)->getPayload();
                    if (data == "" || socketIdx == -1) {
                        continue;
                    } else {
                        saveFile(filePath, data);
                        ++success;
                        ++it;
                        if (success == 1) {
                            // 获取第一张图片作为下载项目的预览缩略图
#if defined(_WIN32)
                            emit previewImageSignal(code->toUnicode(filePath.c_str()).toStdString());
#elif defined(__APPLE__)
                            emit previewImageSignal(filePath);
#endif
                        }
                        emit downloadProgressSignal(total, success); // 发送信号使下载窗口更新显示
                    }
                }
                filePath = {}; // 文件名重置
            }
        }

        ClientSocket::disconnectToServer(socketIdx);

        // 将下载状态置为下载完成
        this->stateWidget->setState(downloadState::SUCCESS);
        emit downloadCompleteSignal(); // 发射下载完成信号
        return;
    };

    std::thread t(f);
    t.detach();
    return;
}

void PixivDownloadItem::telegramDownload() {
    ////将下载状态置为下载中
    // this->stateWidget->setState(downloadState::DOWNLOADING);
    // std::string url = downloadUrl;
    // std::string path = downloadPath;

    ////lambd表达式作为子线程运行
    // auto f = [=]() {
    //	std::string refer = url;		//原url作为refer
    //	UrlParser* urlP = new UrlParser();
    //	urlP->parseUrl(url);
    //	//组装请求json文件报文
    //	HttpRequest* jsonHttpRequest = new HttpRequest(*urlP);
    //	jsonHttpRequest->referer = refer;
    //	jsonHttpRequest->accept = "*/*";
    //	jsonHttpRequest->acceptCharset = "";
    //	//请求json文件
    //	std::string* json = new std::string;
    //	*json = M->requestHtml(*urlP, jsonHttpRequest->request());
    //	//http请求失败
    //	while (*json == EMPTY_STRING || json->size() == 3) {
    //		//更改状态为http请求失败
    //		this->stateWidget->setState(downloadState::HTTPREQUESTFAILED);
    //		//重试直到请求成功
    //		jsonHttpRequest->cookie = _pixivCookie;
    //		*json = M->requestHtml(*urlP, jsonHttpRequest->request());
    //	}
    //	//更改状态为下载中
    //	this->stateWidget->setState(downloadState::DOWNLOADING);
    //	delete jsonHttpRequest;
    //	delete urlP;
    //	//提取图片url
    //	std::vector<std::string> Vurl;//存放url的向量数组
    //	int total = M->parseHtmlForUrl(*json, Vurl, "(?:file)/[\\S]+.(?:jpg|png)");//总图片数
    //	int success{ 0 };//下载成功个数
    //	emit downloadProgressSignal(total, success);//发送信号使下载窗口更新显示
    //	delete json;

    //	std::vector<std::string>::iterator it = Vurl.begin();	//存放url的vector迭代器
    //	//url解析类
    //	UrlParser imageUrl;

    //	//创建http请求报文类
    //	HttpRequest imageHttpRequest;
    //	imageHttpRequest.referer = refer;
    //	imageHttpRequest.accept = "image/*";

    //	//图片文件路径
    //	std::string filePath{};

    //	while (it != Vurl.end()) {
    //		//解析图片url
    //		imageUrl.parseUrl("https://telegra.ph/" + *it);
    //		//组装对应url请求报文
    //		imageHttpRequest.remakeRequest(imageUrl);
    //		//文件路径utf-8转GB2312，确保正确打开中文路径文件
    //		QTextCodec* code = QTextCodec::codecForName("GB2312");
    //		filePath = code->fromUnicode((path + "/" + std::to_string(success) + imageUrl.fileExtension).c_str());

    //		if (mDownload.fileDownload_nonreuse(imageUrl, filePath, imageHttpRequest.request())) {
    //			++success;
    //			it++;					//迭代器递增，下载下一张图片
    //			if (success == 1) {		//获取第一张图片作为下载项目的预览缩略图
    //				emit previewImageSignal(code->toUnicode(filePath.c_str()).toStdString());
    //			}
    //			emit downloadProgressSignal(total, success);//发送信号使下载窗口更新显示
    //		}
    //		filePath = {};	//文件名重置
    //	}

    //	//将下载状态置为下载完成
    //	this->stateWidget->setState(downloadState::SUCCESS);
    //	emit downloadCompleteSignal();//发射下载完成信号

    //	return;
    //	};

    // std::thread t(f);
    // t.detach();

    // return;
}

// PixivDownloadTopWidget
PixivDownloadTopWidget::PixivDownloadTopWidget() {
    // 组件按钮
    foldButton = new AnimationButton("", ICON_FOLD, PIXIV_DOWNLOAD_FOLD_BUTTON_SIZE, 4);
    unfoldButton = new AnimationButton("", ICON_UNFOLD, PIXIV_DOWNLOAD_FOLD_BUTTON_SIZE, 4);
    countLabel = new TextLabel();
    layout = new QHBoxLayout();

    // 设置按钮大小
    foldButton->setFixedSize(PIXIV_DOWNLOAD_FOLD_BUTTON_SIZE);
    unfoldButton->setFixedSize(PIXIV_DOWNLOAD_FOLD_BUTTON_SIZE);

    connect(this->foldButton, &QPushButton::clicked, this, &PixivDownloadTopWidget::foldButtonClicked);
    connect(this->unfoldButton, &QPushButton::clicked, this, &PixivDownloadTopWidget::unfoldButtonClicked);

    // 总数标签初始显示
    countLabel->setText("0");

    // 布局管理
    layout->addWidget(countLabel);
    countLabel->hide();

    layout->addStretch(1);
    layout->addWidget(foldButton);
    layout->addWidget(unfoldButton);
    layout->setSpacing(MARGIN_WIDTH / 2);
    layout->setMargin(0);
    this->setLayout(layout);
}

// PixivDownloadItemWidget
PixivDownloadItemWidget::PixivDownloadItemWidget() : TransparentWidget() {

    // 注册std::string作为信号槽参数
    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<std::vector<std::string>>("std::vector<std::string>");

    // item窗口链表初始化
    itemList = std::list<PixivDownloadItem*>();
    // 哈希表初始化
    hashTable = std::unordered_set<std::string>();
    Glayout = new QGridLayout();

    // itemList添加头节点
    itemList.emplace_back(nullptr);

    // 设置聚焦策略
    this->setFocusPolicy(Qt::FocusPolicy::TabFocus);

    // 信号与槽连接
    connect(this, &PixivDownloadItemWidget::itemAddedSignal, this,
            &PixivDownloadItemWidget::checkDownloadingOrNot); /*有下载项目加入后，检测是否需要唤醒下载队列
                                                              下载正在进行则不唤醒，没有正在下载项目则唤醒*/
    connect(this, &PixivDownloadItemWidget::startDownloadSignal, this,
            &PixivDownloadItemWidget::startDownload); // 收到开始下载信号，开始下载当前队首项目

    connect(this, &PixivDownloadItemWidget::adjustLayoutSignal, this,
            &PixivDownloadItemWidget::adjustLayout); // 收到布局行列改变信号，重新布局

    connect(this, &PixivDownloadItemWidget::urlIsSingleWorkSignal, this,
            &PixivDownloadItemWidget::addDownloadItem); // url是单个作品url，则创建一个下载窗口

    connect(this, &PixivDownloadItemWidget::urlIsAllWorkSignal, this,
            &PixivDownloadItemWidget::getPixivAllIllustsUrl); // url是用户所有作品url，则发送请求获取每一个作品url

    connect(this, &PixivDownloadItemWidget::urlIsTaggedWorkSignal, this,
            &PixivDownloadItemWidget::
                getPixivTaggedIllustsUrl); // url是用户筛选后作品url，则发送请求获取筛选后每一个作品url

    connect(this, &PixivDownloadItemWidget::initLoadItemSignal, this, &PixivDownloadItemWidget::initLoadItem);

    Glayout->setMargin(0);               // 布局周围间距为零
    Glayout->setAlignment(Qt::AlignTop); // 默认上对齐
    this->setLayout(Glayout);

    // 加载未完成下载项目
    loadDownloadData();
}

void PixivDownloadItemWidget::initLoadItem(const std::string& url, const std::string& downloadPath) {
    // 添加进链表数组中
    itemList.emplace_back(new PixivDownloadItem(url, downloadPath, this->foldOrUnfold));
    // 初始化迭代器
    if (itemList.size() == 2) {
        downloadingItem = itemList.cbegin();
    }

    emit adjustLayoutSignal(); // 刷新布局
    emit itemAddedSignal();    // 发送信号提示有新项目加入
}

void PixivDownloadItemWidget::addDownloadItem(const std::string& url, const std::string& downloadPath) {
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
    itemList.emplace_back(new PixivDownloadItem(url, downloadPath, this->foldOrUnfold));
    // 保存下载信息
    saveDownloadData(url + "\n" + downloadPath);

    // 初始化迭代器
    if (itemList.size() == 2) {
        downloadingItem = itemList.cbegin();
    }

    emit adjustLayoutSignal(); // 刷新布局
    emit itemAddedSignal();    // 发送信号提示有新项目加入
}

void PixivDownloadItemWidget::checkUrl(const std::string& url) { // 判断url格式
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

void PixivDownloadItemWidget::getPixivAllIllustsUrl(const std::string& id) {
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

void PixivDownloadItemWidget::getPixivTaggedIllustsUrl(const std::string& id, const std::string& tag) {
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

void PixivDownloadItemWidget::startDownload() {
    // 有待下载项目则迭代器迭代
    this->downloadingItem++;
    // 开始下载后绑定正在下载的项目的完成信号和downloadCompleted();
    connect(*downloadingItem, &PixivDownloadItem::downloadCompleteSignal, this,
            &PixivDownloadItemWidget::downloadCompleted);

    this->downloadingOrNot = true;      // 标记正在下载
    (*downloadingItem)->checkUrlType(); // 开始下载
    return;
}

void PixivDownloadItemWidget::checkDownloadingOrNot() {
    if (downloadingOrNot) {
        return;
    }
    if (!downloadingOrNot) {
        emit startDownloadSignal();
        return;
    }
}

void PixivDownloadItemWidget::downloadCompleted() {
    // 解绑下载完成项目的downloadCompleteSignal()信号和downloadCompleted()函数
    disconnect(*downloadingItem, &PixivDownloadItem::downloadCompleteSignal, this,
               &PixivDownloadItemWidget::downloadCompleted);
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

void PixivDownloadItemWidget::caculateColumn() {
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

void PixivDownloadItemWidget::adjustLayout() {
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

void PixivDownloadItemWidget::foldDownloadItems() {
    for (auto it = ++this->itemList.cbegin(); it != this->itemList.cend(); ++it) {
        (*it)->previewWidgetVisiable(false);
        this->foldOrUnfold = false;
        (*it)->setFixedHeight(PIXIV_DOWNLOAD_ITEM_WITHOUT_PIC_HEIGHT);
    }
    emit adjustLayoutSignal();
    return;
}

void PixivDownloadItemWidget::unfoldDownloadItems() {
    for (auto it = ++this->itemList.cbegin(); it != this->itemList.cend(); ++it) {
        (*it)->previewWidgetVisiable(true);
        this->foldOrUnfold = true;
        (*it)->setFixedHeight(PIXIV_DOWNLOAD_ITEM_WITH_PIC_HEIGHT);
    }
    emit adjustLayoutSignal();
    return;
}

void PixivDownloadItemWidget::loadDownloadData() {
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
        // emit itemAddedSignal();//发送信号提示有新项目加入
        return;
    };

    std::thread th(f);
    th.detach();
    return;
}

// PixivDownloadWidget
PixivDownloadWidget::PixivDownloadWidget() {
    // 记录宽度
    this->wWidth = this->width();
    // 初始化组件
    topWidget = new PixivDownloadTopWidget();
    itemWidget = new PixivDownloadItemWidget();
    scrollArea = new TransparentScrollArea();
    layout = new QVBoxLayout();

    // 信号槽实现窗口大小改变，重新计算pixiv下载窗口布局
    connect(this, &PixivDownloadWidget::sizeChangedSignal, this->itemWidget, &PixivDownloadItemWidget::caculateColumn);

    // 信号与槽实现 top窗口按钮 控制 下载项目 展开或折叠
    connect(this->topWidget, &PixivDownloadTopWidget::foldButtonClicked, this->itemWidget,
            &PixivDownloadItemWidget::foldDownloadItems);
    connect(this->topWidget, &PixivDownloadTopWidget::unfoldButtonClicked, this->itemWidget,
            &PixivDownloadItemWidget::unfoldDownloadItems);

    // 设置滚动窗口
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidget(itemWidget);
    scrollArea->setWidgetResizable(true);

    // 布局管理
    layout->addWidget(topWidget);
    layout->addSpacing(5);
    layout->addWidget(scrollArea);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);
}

void PixivDownloadWidget::checkUrl(const std::string& url) {
    this->itemWidget->checkUrl(url);
}

void PixivDownloadWidget::onChangedRepaint() {
    this->itemWidget->caculateColumn();
}

void PixivDownloadWidget::resizeEvent(QResizeEvent* ev) {
    this->itemWidget->setMaximumWidth(this->width());
    this->itemWidget->resize(sizeHint());
    if (abs(this->width() - wWidth) > 7) {
        wWidth = this->width();
        emit sizeChangedSignal();
    }
}

// PixivWidget
PixivWidget::PixivWidget() {
    // 初始化布局
    layout = new QVBoxLayout();

    // 初始化窗口
    inputWidget = new PixivUrlInputWidget();
    downloadWidget = new PixivDownloadWidget();

    // 信号与槽：收到url后,检查url类型
    connect(inputWidget, &PixivUrlInputWidget::inputUrlSignal, downloadWidget, &PixivDownloadWidget::checkUrl);

    // 窗口加入布局，修改布局样式
    layout->addWidget(inputWidget);
    layout->addWidget(downloadWidget);
    layout->setContentsMargins(0, 0, MARGIN_WIDTH, 0);

    // 设置布局
    setLayout(layout);
}

void PixivWidget::onChangedRepaint() {
    this->downloadWidget->onChangedRepaint();
}