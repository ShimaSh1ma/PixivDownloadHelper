#include "PixivWidget/PixivItemWidget.h"

#include <regex>
#include <thread>

#include <QtGui/qdesktopservices.h>

#include <SocketModule/ClientSocket.h>
#include <SocketModule/HttpRequest.h>
#include <SocketModule/HttpResponseParser.h>
#include <SocketModule/UrlParser.h>

#include "publicFunction.h"

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
            ClientSocket::releaseSocket(SFD);
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
                filePath = path + "/" + imageUrl.fileName + imageUrl.fileExtension;
                if (socketIdx == -1) {
                    break;
                }
                if (ClientSocket::socketSend(socketIdx, imageHttpRequest.httpRequest())) {
                    std::unique_ptr<HttpResponseParser> tempP = ClientSocket::socketReceive(socketIdx);
                    if (tempP == nullptr) {
                        break;
                    }
                    std::string data = tempP->getPayload();
                    if (data == "" || socketIdx == -1) {
                        break;
                    } else {
                        saveFile(filePath, data);
                        ++success;
                        ++it;
                        if (success == 1) {
                            // 获取第一张图片作为下载项目的预览缩略图
                            emit previewImageSignal(filePath);
                        }
                        emit downloadProgressSignal(total, success); // 发送信号使下载窗口更新显示
                    }
                }
                filePath = {}; // 文件名重置
            }
        }

        ClientSocket::releaseSocket(socketIdx);

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