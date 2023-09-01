#include "SettingWidget.h"

//SubSettingWidget
SubSettingWidget::SubSettingWidget() {
	//组件初始化
	layout = new QVBoxLayout;
	changeDirWidget = new ChangeDownloadPathWidget;
	changePixivCookieWidget = new ChangePixivCookieWidget;
	changeTransparencyWidget = new ChangeTransparencyWidget;
	changeBackImageWidget = new ChangeBackgroundImageWidget;

	//布局管理
	layout->addWidget(changeDirWidget);
	layout->addWidget(changePixivCookieWidget);
	layout->addWidget(changeTransparencyWidget);
	layout->addWidget(changeBackImageWidget);
	layout->addStretch(1);

	layout->setMargin(0);

	setLayout(layout);
}

SubSettingWidget::~SubSettingWidget() {
	delete layout;
	delete changeDirWidget;
	delete changePixivCookieWidget;
	delete changeTransparencyWidget;
	delete changeBackImageWidget;
}

//ChangeDownloadPathWidget
ChangeDownloadPathWidget::ChangeDownloadPathWidget() {
	//组件初始化
	layout = new QGridLayout;

	title = new textLabel;
	pathEdit = new DirEdit;
	changeButton = new ToolButton(tr("Change Path"));
	//标题标签设置
	title->setText(tr("Change Download Path"));
	//显示下载路径的文本框设置
	pathEdit->setReadOnly(true);//只读
	pathEdit->setText(QString::fromStdString(_downloadPath));
	pathEdit->setFixedHeight(_settingChangeDownloadPathLineEdit_size.height());
	pathEdit->setMinimumWidth(_settingChangeDownloadPathLineEdit_size.width());

	//信号与槽连接
	connect(this->changeButton, &ToolButton::clicked, this,
		&ChangeDownloadPathWidget::chooseDownloadPath);//按下change按钮改变下载路径

	//布局管理
	layout->addWidget(title, 0, 0);
	layout->addWidget(pathEdit, 1, 0);
	layout->addWidget(changeButton, 1, 1);

	this->setLayout(layout);
}

ChangeDownloadPathWidget::~ChangeDownloadPathWidget() {
	delete title;
	delete layout;
	delete pathEdit;
	delete changeButton;
}

void ChangeDownloadPathWidget::chooseDownloadPath() {
	//打开文件资源管理器选择下载文件夹
	std::string temp = QFileDialog::getExistingDirectory(nullptr, nullptr, _downloadPath.c_str()).toStdString();

	if (temp != "") {
		_downloadPath = temp;
		//更新下载路径显示
		this->pathEdit->setText(QString::fromStdString(_downloadPath));
		//更改设置文件
		changeDownloadPath();
	}
}

//ChangePixivCookieWidget
ChangePixivCookieWidget::ChangePixivCookieWidget() {
	//初始化组件
	layout = new QGridLayout;
	textEdit = new TransparentTextEdit;
	changeButton = new ToolButton(tr("Change"));
	saveButton = new ToolButton(tr("Save"));
	title = new textLabel;
	//标题设置
	title->setText(tr("Change Pixiv Cookie"));
	//显示文本框设置
	textEdit->setMinimumSize(_settingChangePixivCookieTextEdit_size);//设置最小大小
	textEdit->setText(QString::fromStdString(_pixivCookie));//展示现在的cookie
	textEdit->setReadOnly(true);//只读，在点击change按钮后可编辑,点击Save后恢复只读状态

	//信号与槽连接
	connect(changeButton, &ToolButton::clicked,
		this, &ChangePixivCookieWidget::turnEditable);//按下change按钮，编辑cookie
	connect(saveButton, &ToolButton::clicked,
		this, &ChangePixivCookieWidget::saveCookie);//按下save按钮，保存cookie设置

	//布局管理
	layout->addWidget(title, 0, 0);
	layout->addWidget(changeButton, 3, 1, 1, 1);
	layout->addWidget(saveButton, 3, 2, 1, 1);
	layout->addWidget(textEdit, 1, 0, 2, 3);
	//文本框和修改按钮默认不可见
	this->textEdit->setVisible(false);
	this->changeButton->setVisible(false);
	this->saveButton->setVisible(false);

	this->setLayout(layout);
}

ChangePixivCookieWidget::~ChangePixivCookieWidget(){
	delete textEdit;
	delete changeButton;
	delete saveButton;
	delete title;
	delete layout;
}

void ChangePixivCookieWidget::saveCookie() {
	//更改_pixivCookie
	_pixivCookie = this->textEdit->toPlainText().toStdString();
	//设置为只读
	this->textEdit->setReadOnly(true);
	//更新设置文件
	changePixivCookie();

	this->textEdit->setStyleSheet(
		"background-color:rgba(255,255,255,0);"
	);
}

void ChangePixivCookieWidget::turnEditable() {
	this->textEdit->setReadOnly(false);
	this->textEdit->setStyleSheet(
		"background-color:rgba(255,255,255,180);"
		"border-radius:8px;"
	);
}

void ChangePixivCookieWidget::mousePressEvent(QMouseEvent* mouseE) {
	if (this->showOrNot) {
		this->textEdit->setVisible(false);
		this->changeButton->setVisible(false);
		this->saveButton->setVisible(false);
		this->showOrNot = false;
	}
	else if (!this->showOrNot) {
		this->textEdit->setVisible(true);
		this->changeButton->setVisible(true);
		this->saveButton->setVisible(true);
		this->showOrNot = true;
	}
}

//ChangeTransparencyWidget
ChangeTransparencyWidget::ChangeTransparencyWidget() {
	//组件初始化
	title = new textLabel;
	slider = new QSlider(Qt::Horizontal);
	layout = new QGridLayout;
	//标题设置
	title->setText(tr("Change Window Transparency"));
	//滑动条设置
	slider->setRange(0, _windowTransparency_division);//设置范围
	slider->setValue(_windowTransparency);//设置默认值
	//布局管理
	layout->addWidget(title, 0, 0);
	layout->addWidget(slider, 1, 0);

	//信号与槽函数
	connect(this->slider, &QSlider::sliderReleased,
		this, &ChangeTransparencyWidget::saveTranparency);//释放滚动条时，保存透明度信息

	this->setLayout(layout);
}

ChangeTransparencyWidget::~ChangeTransparencyWidget(){
	delete title;
	delete slider;
	delete layout;
}

void ChangeTransparencyWidget::saveTranparency() {
	//保存透明度信息
	changeWindowTransparency();
}

//ChangeBackgroundImageWidget
ChangeBackgroundImageWidget::ChangeBackgroundImageWidget() {
	//初始化组件
	layout = new QGridLayout;
	title = new textLabel;
	imageView = new QLabel;
	changeButton = new ToolButton(tr("Change"));
	//标题标签设置
	title->setText(tr("Change Background"));
	//缩略图窗口设置
	imageView->setFixedSize(_settingChangeBackgroundLabel_size);//设置缩略图窗口大小
	QPixmap pix(_backgroundPicturePath.c_str());//加载图片
	imageView->setPixmap(pix.scaled(imageView->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));//缩放适应大小

	//信号与槽连接
	connect(this->changeButton, &ToolButton::clicked,
		this, &ChangeBackgroundImageWidget::chooseImage);//按下切换按钮，选择背景图片

	//布局管理
	layout->addWidget(title, 0, 0);
	layout->addWidget(new QLabel, 0, 1);
	layout->addWidget(imageView, 1, 0);
	layout->addWidget(changeButton, 1, 3);

	this->setLayout(layout);
}

ChangeBackgroundImageWidget::~ChangeBackgroundImageWidget(){
	delete title;
	delete imageView;
	delete changeButton;
	delete layout;
}

void ChangeBackgroundImageWidget::chooseImage() {
	std::string temp = QFileDialog::getOpenFileName(NULL, "Background", "./", "Image(*.png *.jpg)").toStdString();

	if (temp != "") {
		//打开文件资源管理器选择背景图片路径
		_backgroundPicturePath = temp;
		//缩略图窗口加载选择好的背景图片
		QPixmap pix(_backgroundPicturePath.c_str());
		imageView->setPixmap(pix.scaled(imageView->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
		//更新设置文件
		changeBackgroundImagePath();
		//发送背景图片更改信号，供主窗口刷新
		emit backgroundChanged();
	}
}

//SettingWidget
SettingWidget::SettingWidget() {
	//初始化组件
	subWidget = new SubSettingWidget;
	scrollArea = new TransparentScrollArea;
	layout = new QVBoxLayout;
	//设置滚动窗口
	scrollArea->setWidget(subWidget);//指定窗口
	scrollArea->setWidgetResizable(true);//设置窗口可缩放
	scrollArea->setMinimumWidth(subWidget->minimumWidth());
	//布局管理
	layout->setMargin(0);
	layout->addWidget(scrollArea);

	this->setLayout(layout);
}

SettingWidget::~SettingWidget() {
	delete subWidget;
	delete scrollArea;
	delete layout;
}