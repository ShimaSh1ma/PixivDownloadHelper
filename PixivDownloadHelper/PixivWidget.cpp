#include "PixivWidget.h"
//PixivUrlInputWidget
PixivUrlInputWidget::PixivUrlInputWidget(): TranslucentWidget(){
	setMinimumSize(_pixivUrlWidget_size);//设置最小大小
	setMaximumHeight(_pixivUrlWidget_size.height());

	//初始化布局
	layout = new QHBoxLayout;

	//初始化控件
	edit = new PixivUrlEdit;
	dButton = new ToolButton("Download");

	//控件加入布局
	layout->addWidget(edit);
	layout->addWidget(dButton);

	//信号与槽连接
	connect(edit, &PixivUrlEdit::returnPressed,
		dButton, &ToolButton::click);//文本框按下回车触发下载按钮点击效果

	connect(dButton, &QPushButton::clicked,
		edit, &PixivUrlEdit::sendText);//按下下载按钮，文本框发送携带文本内容的Text信号

	//应用布局
	this->setLayout(layout);
}

PixivUrlInputWidget::~PixivUrlInputWidget() {
	delete layout;
	delete dButton;
	delete edit;
}

//PixivDownloadItemTitleWidget
PixivDownloadItemTitleWidget::PixivDownloadItemTitleWidget(const std::string& url) {
	//大小设置
	setFixedHeight(_pixivDownloadItemTitle_height);

	//组件初始化
	urlLabel = new textLabel;
	layout = new QHBoxLayout;
	//保存url
	downloadUrl = url;
	//url显示标签设置
	urlLabel->setText(tr(downloadUrl.c_str()));
	urlLabel->setMinimumWidth(200);
	urlLabel->setAlignment(Qt::AlignCenter);//居中显示
	//布局设置
	layout->addWidget(urlLabel);

	layout->setMargin(0);
	this->setLayout(layout);
}

PixivDownloadItemTitleWidget::~PixivDownloadItemTitleWidget() {
	delete layout;
	delete urlLabel;
}

std::string PixivDownloadItemTitleWidget::getDownloadUrl() {
	return this->downloadUrl;
}

//PixivDownloadItemPreviewWidget
PixivDownloadItemPreviewWidget::PixivDownloadItemPreviewWidget() {
	//组件初始化
	previewImage = new QLabel;
	layout = new QHBoxLayout;

	//设置缩略图
	previewImage->setFixedSize(_pixivDownloadItemPreviewImage_size);//设置最小大小
	QPixmap pix(_default_preview_path.c_str());//加载默认预览图
	previewImage->setPixmap(pix.scaled(previewImage->size(),
		Qt::KeepAspectRatio, Qt::SmoothTransformation));//缩放预览图适应窗口大小
	previewImage->setAlignment(Qt::AlignCenter);//居中显示

	//布局设置
	layout->addWidget(previewImage);
	layout->setMargin(0);

	this->setLayout(layout);
}

PixivDownloadItemPreviewWidget::~PixivDownloadItemPreviewWidget() {
	delete layout;
	delete previewImage;
}

void PixivDownloadItemPreviewWidget::loadPreviewImage(const std::string& imagePath) {
	//保存缩略图路径
	this->previewImagePath = imagePath;

	auto f = [&]() {
		QPixmap* pix = new QPixmap(this->previewImagePath.c_str());//加载缩略图
		previewImage->setPixmap(pix->scaled(previewImage->size(),
			Qt::KeepAspectRatio, Qt::SmoothTransformation));//缩放缩略图适应窗口大小
		delete pix;
	};

	std::thread thd(f);
	thd.detach();
	return;
}

//PixivDownloadItemStateWidget
PixivDownloadItemStateWidget::PixivDownloadItemStateWidget() {
	//注册下载状态枚举量
	qRegisterMetaType<downloadState>("downloadState");
	//大小设置
	setFixedHeight(_pixivDownloadItemState_height);
	//组件初始化
	totalCountLabel = new textLabel;
	successCountLabel = new textLabel;
	separatorLabel = new textLabel;
	downloadStateLabel = new textLabel;
	layout = new QHBoxLayout;
	//数量显示标签设置
	successCountLabel->setFixedSize(80, 20);
	separatorLabel->setFixedSize(10, 20);
	totalCountLabel->setFixedSize(60, 20);

	successCountLabel->setAlignment(Qt::AlignCenter);//居中显示
	separatorLabel->setAlignment(Qt::AlignCenter);
	totalCountLabel->setAlignment(Qt::AlignCenter);

	successCountLabel->setText(QString::number(successCount) + "(succeed)");
	separatorLabel->setText("/");
	totalCountLabel->setText(QString::number(imageCount) + "(total)");

	//下载状态显示标签设置
	downloadStateLabel->setText(tr("Waiting"));
	downloadStateLabel->setFixedSize(120, 20);
	downloadStateLabel->setAlignment(Qt::AlignCenter);
	//布局管理
	layout->addStretch(1);
	layout->addWidget(successCountLabel);
	layout->addWidget(separatorLabel);
	layout->addWidget(totalCountLabel);
	layout->addWidget(downloadStateLabel);
	layout->addStretch(1);
	layout->setMargin(0);

	this->setLayout(layout);
}

PixivDownloadItemStateWidget::~PixivDownloadItemStateWidget() {
	delete totalCountLabel;
	delete successCountLabel;
	delete separatorLabel;
	delete downloadStateLabel;
	delete layout;
}

void PixivDownloadItemStateWidget::setState(const downloadState& _state) {
	this->state = _state;//更改下载状态
	this->downloadStateLabel->setText(//更新下载状态显示
		tr(downloadStateString().toStdString().c_str()));
}

void PixivDownloadItemStateWidget::setProgress(const int& total,const int& success) {
	this->imageCount = total;
	this->successCount = success;
	//图片数量标签设置
	successCountLabel->setText(QString::number(successCount) + "(succeed)");
	totalCountLabel->setText(QString::number(imageCount) + "(total)");
}

QString PixivDownloadItemStateWidget::downloadStateString() {
	if (this->state == downloadState::DOWNLOADING) {
		return "Downloading";
	}
	else if (this->state == downloadState::WAITING) {
		return "Waiting";
	}
	else if (this->state == downloadState::SUCCESS) {
		return "Succeed";
	}
	else if (this->state == downloadState::HTTPREQUESTFAILED) {
		return "HttpRequestFailed";
	}
}

//PixivDownloadItem
PixivDownloadItem::PixivDownloadItem(const std::string& _url, const std::string _path)
	:downloadPath(_path) {
	qRegisterMetaType<std::string>("std::string");//注册std::string作为信号槽参数

	//大小限定
	setFixedHeight(_pixivDownloadItemWithPre_height);
	setMaximumWidth(_pixivDownloadItem_maxWidth);
	setMinimumWidth(_pixivDownloadItem_minWidth);

	//组件初始化
	titleWidget = new PixivDownloadItemTitleWidget(_url);
	previewWidget = new PixivDownloadItemPreviewWidget;
	stateWidget = new PixivDownloadItemStateWidget;
	layout = new QVBoxLayout;

	//信号与槽连接
	connect(this, &PixivDownloadItem::downloadProgressSignal,
		this->stateWidget, &PixivDownloadItemStateWidget::setProgress);//接收下载进度变化并刷新显示

	connect(this, &PixivDownloadItem::previewImageSignal,
		this->previewWidget, &PixivDownloadItemPreviewWidget::loadPreviewImage);//收到缩略图路径信号，更新缩略图

	//布局管理
	layout->addWidget(titleWidget);
	layout->addWidget(previewWidget);
	layout->addWidget(stateWidget);

	this->layout->setMargin(10);
	this->setLayout(layout);
}

PixivDownloadItem::~PixivDownloadItem() {
	delete titleWidget;
	delete previewWidget;
	delete stateWidget;
	delete layout;
}

void PixivDownloadItem::mousePressEvent(QMouseEvent* mouseE) {
	if (mouseE->button() == Qt::LeftButton) {	//左键单击事件
		if (showOrNot) {
			this->previewWidget->setVisible(false);
			this->showOrNot = false;
			setFixedHeight(_pixivDownloadItemWithoutPre_height);
		}
		else if (!showOrNot) {
			this->previewWidget->setVisible(true);
			this->showOrNot = true;
			setFixedHeight(_pixivDownloadItemWithPre_height);
		}
	}
}

bool PixivDownloadItem::getShowOrNot() {
	return this->showOrNot;
}

void PixivDownloadItem::pixivDownload() {
	//将下载状态置为下载中
	this->stateWidget->setState(downloadState::DOWNLOADING);
	std::string url = this->titleWidget->getDownloadUrl();//下载url
	std::string path = this->downloadPath;//下载路径

	//lambd表达式作为子线程运行
	auto f = [=]() {	
	std::string refer = url;		//原url作为refer
	std::string* ajaxurl = new std::string;//pixiv ajax接口url生成
	*ajaxurl = pixivAjaxurl(url);
	if (*ajaxurl == "") {
		delete ajaxurl;
		return;
	}

	UrlParser* urlP = new UrlParser;
	urlP->parseUrl(*ajaxurl);
	delete ajaxurl;

	//组装请求json文件报文
	HttpRequest* jsonHttpRequest = new HttpRequest(*urlP);
	jsonHttpRequest->referer = refer;
	jsonHttpRequest->accept = "*/*";
	jsonHttpRequest->acceptCharset = "";
	jsonHttpRequest->cookie = _pixivCookie;
	qDebug() << jsonHttpRequest->request().c_str() << "\r\n";
	MHttpDownload* M = new MHttpDownload;
	//请求json文件
	std::string* json = new std::string;
	*json = M->requestHtml(*urlP, jsonHttpRequest->request());
	//http请求失败
	while (*json == _EMPTY_STRING || json->size() == 3) {
		//更改状态为http请求失败
		qDebug() << json->c_str() << "\r\n";
		this->stateWidget->setState(downloadState::HTTPREQUESTFAILED);
		//重试直到请求成功
		jsonHttpRequest->cookie = _pixivCookie;
		*json = M->requestHtml(*urlP, jsonHttpRequest->request());
		Sleep(100);
	}
	delete jsonHttpRequest;
	delete urlP;
	//去除json文件中的转义字符
	jsonParse(*json);
	//提取图片url
	std::vector<std::string> Vurl;//存放url的向量数组
	int total = M->parseHtmlForUrl(*json, Vurl, _regex_pixiv_illust_url);//总图片数
	int success{ 0 };//下载成功个数
	emit downloadProgressSignal(total, success);//发送信号使下载窗口更新显示
	delete json;
	delete M;

	while (!Vurl.empty()) {
		std::vector<std::string>::iterator it = Vurl.begin();	//存放url的vector迭代器
		std::vector<std::string> retry;			//暂时存放需要重新下载url的vector
		//url解析类
		UrlParser imageUrl;

		//创建http请求报文类
		HttpRequest imageHttpRequest;
		imageHttpRequest.referer = refer;
		imageHttpRequest.accept = "image/*";

		//下载函数类
		MHttpDownload mDownload;

		//图片文件路径
		std::string filePath{};

		while (it != Vurl.end()) {
			//解析图片url
			imageUrl.parseUrl(*it);
			//组装对应url请求报文
			imageHttpRequest.refreshUrl(imageUrl);
			//文件路径utf-8转GB2312，确保正确打开中文路径文件
			QTextCodec* code = QTextCodec::codecForName("GB2312");
			filePath = code->fromUnicode((path + "\\" + imageUrl.fileName).c_str());

			if (!mDownload.fileDownload_nonreuse(imageUrl, filePath, imageHttpRequest.request())) {
				retry.push_back(*it);
			}
			else {
				++success;
				if (success == 1) {		//获取第一张图片作为下载项目的预览缩略图
					emit previewImageSignal(code->toUnicode(filePath.c_str()).toStdString());
				}
				emit downloadProgressSignal(total, success);//发送信号使下载窗口更新显示
			}
			filePath = {};	//文件名重置
			it++;			//迭代器递增，下载下一张图片
		}
		Vurl = retry;
	}

	//将下载状态置为下载完成
	this->stateWidget->setState(downloadState::SUCCESS);
	emit downloadCompleteSignal();//发射下载完成信号

	return;
	};

	std::thread t(f);
	t.detach();

	return;
}

//PixivDownloadItemWidget
PixivDownloadItemWidget::PixivDownloadItemWidget() :TransparentWidget() {
	//注册std::string作为信号槽参数
	qRegisterMetaType < std::string >("std::string");

	//item窗口向量组初始化
	itemVector = new std::vector<PixivDownloadItem*>;
	Glayout = new QGridLayout;

	//信号与槽连接
	connect(this, &PixivDownloadItemWidget::itemAddedSignal,
		this, &PixivDownloadItemWidget::checkDownloadingOrNot);/*有下载项目加入后，检测是否需要唤醒下载队列
															   下载正在进行则不唤醒，没有正在下载项目则唤醒*/

	connect(this, &PixivDownloadItemWidget::downloadStartSignal,
		this, &PixivDownloadItemWidget::startDownload);//收到开始下载信号，开始下载当前队首项目

	connect(this, &PixivDownloadItemWidget::sizeChangeSignal,
		this, &PixivDownloadItemWidget::caculateColumn);//窗口改变则重新计算布局行列数

	connect(this, &PixivDownloadItemWidget::refreshLayoutSignal,
		this, &PixivDownloadItemWidget::adjustLayout);//收到布局行列改变信号，重新布局

	connect(this, &PixivDownloadItemWidget::urlIsSingleWorkSignal,
		this, &PixivDownloadItemWidget::addDownloadItem);//url是单个作品url，则创建一个下载窗口

	connect(this, &PixivDownloadItemWidget::urlIsAllWorkSignal,
		this, &PixivDownloadItemWidget::getPixivAllIllustsUrl);//url是用户所有作品url，则发送请求获取每一个作品url

	connect(this, &PixivDownloadItemWidget::urlIsTaggedWorkSignal,
		this, &PixivDownloadItemWidget::getPixivTaggedIllustsUrl);//url是用户筛选后作品url，则发送请求获取筛选后每一个作品url

	Glayout->setMargin(0);//布局周围间距为零
	Glayout->setAlignment(Qt::AlignTop);//默认上对齐
	this->setLayout(Glayout);
}

PixivDownloadItemWidget::~PixivDownloadItemWidget(){
	delete Glayout;
	delete itemVector;
}

void PixivDownloadItemWidget::resizeEvent(QResizeEvent* ev) {
	emit sizeChangeSignal();
}

void PixivDownloadItemWidget::addDownloadItem(const std::string& url) {
	//检查下载路径是否存在，及是否拥有写入权限
	QTextCodec* code = QTextCodec::codecForName("GB2312");
	if (_access(code->fromUnicode(_downloadPath.c_str()), 2)) {
		return;
	}
	//新建一个pixiv下载项目窗口
	PixivDownloadItem* Pitem = new PixivDownloadItem(url, _downloadPath);
	//添加进动态数组中
	itemVector->push_back(Pitem);
	//总项目数+1
	this->itemCount++;

	emit refreshLayoutSignal();//发送信号刷新布局
	emit itemAddedSignal();//发送信号提示有新项目加入
}

void PixivDownloadItemWidget::checkUrl(const std::string& url) {	//判断url格式
	//单个作品url
	std::regex urlSingleWork(_regex_pixiv_artwork_url);
	//用户所有作品url的匹配规则
	std::regex ruleAll(_regex_pixiv_userAll_url);
	//用户按照tag筛选后的url匹配规则
	std::regex ruleTags(_regex_pixiv_userTagged_url);
	std::smatch re;
	//url格式正确则创建下载项目
	if (std::regex_match(url, re, urlSingleWork)) {
		//判断此url下载项目是否已经存在
		for (std::vector<PixivDownloadItem*>::iterator it = itemVector->begin();
			it < itemVector->end(); it++) {
			//项目重复则不创建
			if (url == (*it)->titleWidget->getDownloadUrl()) {
				return;
			}
		}
		emit urlIsSingleWorkSignal(url);//发送信号指示输入是单个作品的url
	}
	else if (std::regex_match(url, re, ruleAll)) {	//url为用户所有作品
		qDebug() << "urlIsAllWorkSignal\r\n";
		emit urlIsAllWorkSignal(re[1].str());
	}
	else if (std::regex_match(url, re, ruleTags)) {	//url为用户筛选后作品
		emit urlIsTaggedWorkSignal(re[1].str(), re[2].str());
	}
	else {
		return;
	}
}

void PixivDownloadItemWidget::getPixivAllIllustsUrl(const std::string& id) {
	auto lamda = [=]() {
		//ajax接口url
		std::string ajaxUrl = "https://www.pixiv.net/ajax/user/" + id + "/profile/all";

		UrlParser* urlP = new UrlParser;
		urlP->parseUrl(ajaxUrl);
		MHttpDownload* M = new MHttpDownload;
		HttpRequest* hr = new HttpRequest(*urlP);
		hr->cookie = _pixivCookie;
		std::string* json = new std::string;
		//请求json
		while (*json == _EMPTY_STRING) {
			*json = M->requestHtml(*urlP, hr->request());
		}

		delete M;
		delete hr;
		delete urlP;

		//json illusts值匹配规则
		std::regex rule("\\{\"illusts\":\\{([^\\}]+)");
		std::smatch re{};
		std::vector<std::string>* url = new std::vector<std::string>;//存放所有作品url的数组
		//预申请空间
		url->reserve(200);
		if (std::regex_search(*json, re, rule)) {
			std::cout << re[1] << "\r\n";
			*json = re[1];
			auto begin = json->cbegin();
			auto end = json->cend();
			//作品id匹配规则
			std::regex insiderule("\"(\\d+)\"");
			//循环匹配所有作品id
			while (std::regex_search(begin, end, re, insiderule)) {
				//作品id转换为url
				url->push_back("https://www.pixiv.net/artworks/" + re[1].str());
				//发射包含作品url的信号
				emit urlIsSingleWorkSignal("https://www.pixiv.net/artworks/" + re[1].str());
				//更改偏移量，继续匹配
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
	auto lamda = [=]() {

		int page{ 0 };//当前页数
		int totalCount{ 0 };//筛选后图片总数
		int pageCount{ 0 };//总页数
		int restCount{ 0 };//最后一页作品数量

		do {
			//ajax接口url
			std::string ajaxUrl = "https://www.pixiv.net/ajax/user/" + id +
				"/illustmanga/tag?tag=" + tag + "&offset=" + std::to_string(page * 48) + "&limit=48&lang=zh";

			UrlParser* urlP = new UrlParser;
			urlP->parseUrl(ajaxUrl);
			MHttpDownload* M = new MHttpDownload;
			HttpRequest* hr = new HttpRequest(*urlP);
			hr->cookie = _pixivCookie;
			std::string* json = new std::string;
			//请求json
			while (*json == _EMPTY_STRING) {
				*json = M->requestHtml(*urlP, hr->request());
			}

			delete M;
			delete hr;
			delete urlP;

			std::smatch re{};

			//获取匹配作品总数
			if (page == 0) {
				std::regex ruleTotal("\"total\":([\\d]+)");
				if (std::regex_search(*json, re, ruleTotal)) {
					totalCount = atoi(re[1].str().c_str());//作品总数
					pageCount = totalCount / 48;		//分页总数
					restCount = totalCount % 48;		//最后一页剩余作品数
				}
			}

			//json illusts值匹配规则
			std::regex rule("\"id\":\"([\\d]{8,9})\"");
			std::vector<std::string> url;
			url.reserve(50);

			auto begin = json->cbegin();
			auto end = json->cend();

			while (std::regex_search(begin, end, re, rule)) {
				//作品id转换为url
				url.push_back("https://www.pixiv.net/artworks/" + re[1].str());
				emit urlIsSingleWorkSignal("https://www.pixiv.net/artworks/" + re[1].str());
				//更改偏移量，继续匹配
				begin = re[1].second;
			}
			delete json;

			page++;//页面数加一
		} while (page < pageCount);

		return;
	};

	std::thread t(lamda);
	t.detach();
}

void PixivDownloadItemWidget::startDownload() {
	//已经达到队尾，没有剩余下载项目
	if (this->downloadingIndex == this->itemCount) {
		return;
	}
	//开始下载后绑定正在下载的项目的完成信号和downloadCompleted();
	connect(this->itemVector->at(this->downloadingIndex), &PixivDownloadItem::downloadCompleteSignal,
		this, &PixivDownloadItemWidget::downloadCompleted);

	this->downloadingOrNot = true;//标记正在下载
	this->itemVector->at(this->downloadingIndex)->pixivDownload();
}

void PixivDownloadItemWidget::checkDownloadingOrNot() {
	if (downloadingOrNot) {
		return;
	}
	if (!downloadingOrNot) {
		emit downloadStartSignal();
	}
}

void PixivDownloadItemWidget::downloadCompleted() {
	//解绑下载完成项目的downloadCompleteSignal()信号和downloadCompleted()函数
	disconnect(this->itemVector->at(this->downloadingIndex), &PixivDownloadItem::downloadCompleteSignal,
		this, &PixivDownloadItemWidget::downloadCompleted);
	//下载状态：未在下载中，下载队列休眠
	this->downloadingOrNot = false;
	//没有待下载项目则返回
	if (this->downloadingIndex == this->itemCount) {
		return;
	}
	//有待下载项目则更新正在下载项目的序号
	this->downloadingIndex++;
	emit downloadStartSignal();
}

void PixivDownloadItemWidget::caculateColumn() {
	//当前列数对应的窗口长度区间
	int maxLength = (this->column + 1) * _pixivDownloadItem_minWidth	//上限
		+ this->column * this->Glayout->spacing();
	int minLength = this->column * _pixivDownloadItem_minWidth	//下限
		+ (this->column - 1) * this->Glayout->spacing();

	//超出区间则更新列数，并发送更新布局的信号
	if (this->size().width() < minLength) {
		this->column--;
		emit refreshLayoutSignal();
	}
	else if (this->size().width() > maxLength) {
		this->column++;
		emit refreshLayoutSignal();
	}
}

void PixivDownloadItemWidget::adjustLayout() {
	//删除原有布局
	delete Glayout;
	Glayout = nullptr;
	//新建布局
	Glayout = new QGridLayout;
	int _row = 0, _column = 0;
	for (auto it = itemVector->begin(); it < itemVector->end(); it++) {
		if (_column < this->column) {
			this->Glayout->addWidget(*it, _row, _column, Qt::AlignTop);
			_column++;
		}
		else {
			_column = 0;
			_row++;
			this->Glayout->addWidget(*it, _row, _column, Qt::AlignTop);
			_column++;
		}
	}

	Glayout->setMargin(0);//布局周围间距为零
	Glayout->setAlignment(Qt::AlignTop);//默认上对齐
	this->setLayout(Glayout);
}

//PixivDownloadWidget
PixivDownloadWidget::PixivDownloadWidget() {
	//初始化组件
	itemWidget = new PixivDownloadItemWidget;
	scrollArea = new TransparentScrollArea;
	layout = new QVBoxLayout;
	//设置滚动窗口
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setWidget(itemWidget);
	scrollArea->setWidgetResizable(true);
	//布局管理
	layout->setMargin(0);
	layout->addWidget(scrollArea);
	this->setLayout(layout);
}

PixivDownloadWidget::~PixivDownloadWidget(){
	delete layout;
	delete itemWidget;
	delete scrollArea;
}

void PixivDownloadWidget::resizeEvent(QResizeEvent* ev) {
	this->itemWidget->setFixedWidth(this->size().width());
}

//PixivWidget
PixivWidget::PixivWidget() {
	//初始化布局 
	layout = new QVBoxLayout;

	//初始化窗口
	uWidget = new PixivUrlInputWidget();
	dWidget = new PixivDownloadWidget();

	//窗口加入布局，修改布局样式
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(uWidget);
	layout->addWidget(dWidget);

	//信号与槽：收到url后,检查url类型
	connect(uWidget->edit, &PixivUrlEdit::TextS, dWidget->itemWidget, &PixivDownloadItemWidget::checkUrl);

	//设置布局
	setLayout(layout);
}

PixivWidget::~PixivWidget() {
	delete layout;
	delete uWidget;
	delete dWidget;
}