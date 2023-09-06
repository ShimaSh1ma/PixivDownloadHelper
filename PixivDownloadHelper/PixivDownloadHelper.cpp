#include "PixivDownloadHelper.h"

PixivDownloadHelper::PixivDownloadHelper(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PixivDownloadHelperClass())
{
    ui->setupUi(this);
    //加载背景图片
    image.load(_backgroundPicturePath.c_str());
    pix = pix.fromImage(image);
    //背景图片缩放
    temp = pix;
    temp = pix.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    this->imageWidth = temp.width();
    this->imageHeight = temp.height();
    //记录窗口大小
    wWidth = this->width();
    wHeight = this->height();

    //初始化布局
    layout = new QGridLayout;

    //初始化窗口
    menuWidget = new MenuWidget;
    pixivWidget = new PixivWidget;
    settingWidget = new SettingWidget;

    stackedWidget = new QStackedWidget;

    //功能窗口加入窗口堆栈，索引返回到对应菜单按钮
    menuWidget->pixivButton->setIndex(stackedWidget->addWidget(pixivWidget));
    menuWidget->settingButton->setIndex(stackedWidget->addWidget(settingWidget));

    //信号槽实现切换窗口
    connect(menuWidget->pixivButton, &MenuButton::indexSignal, stackedWidget, &QStackedWidget::setCurrentIndex);
    connect(menuWidget->settingButton, &MenuButton::indexSignal, stackedWidget, &QStackedWidget::setCurrentIndex);
    //信号槽实现滑块改变背景透明度
    connect(settingWidget->subWidget->changeTransparencyWidget->slider, &QSlider::valueChanged,
        this, &PixivDownloadHelper::changeTransparency);
    //信号槽实现改变背景图片
    connect(settingWidget->subWidget->changeBackImageWidget, &ChangeBackgroundImageWidget::backgroundChanged,
        this, &PixivDownloadHelper::changeBackgroundImage);
    //切换窗口时重新计算下载项目窗口动态布局
    connect(this->stackedWidget, &QStackedWidget::currentChanged,
        this->pixivWidget->downloadWidget->itemWidget, &PixivDownloadItemWidget::caculateColumn);

    //窗口加入布局
    layout->addWidget(menuWidget, 0, 0, 1, 1);
    layout->addWidget(stackedWidget, 0, 1, 2, 2);

    //设置布局
    setLayout(layout);
}

PixivDownloadHelper::~PixivDownloadHelper()
{
    delete layout;
    delete menuWidget;
    delete settingWidget;
    delete pixivWidget;
    delete stackedWidget;
    delete ui;
}

void PixivDownloadHelper::changeTransparency(int transparency) {
    _windowTransparency = transparency;
    this->repaint();
}

void PixivDownloadHelper::changeBackgroundImage() {
    image.load(_backgroundPicturePath.c_str());
    pix = pix.fromImage(image);
    this->repaint();
}

void PixivDownloadHelper::paintEvent(QPaintEvent* paintE) {
    //设置背景
    QPainter painter(this);
    //设置背景图片不透明度
    painter.setOpacity((double)_windowTransparency / _windowTransparency_division);
    //在窗口中心绘制图片
    painter.drawPixmap(xpos, ypos, temp);
}

void PixivDownloadHelper::resizeEvent(QResizeEvent* event) {
    //保持横纵比缩放图片适应窗口大小
    temp = pix;
    temp = pix.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    //更改图片大小缓冲值
    this->imageWidth = temp.width();
    this->imageHeight = temp.height();
    //更改窗口大小缓冲值
    wWidth = this->width();
    wHeight = this->height();
    //计算背景偏移量
    xpos = -(((this->imageWidth - this->width()) / 2 + (temp.width() - this->wWidth) / 2)) / 2;
    ypos = -(((this->imageHeight - this->height()) / 2 + (temp.height() - this->wHeight) / 2)) / 2;
    //调用重绘
    this->repaint();
}