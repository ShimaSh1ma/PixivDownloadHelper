﻿#include "PixivDownloadHelper.h"

PixivDownloadHelper::PixivDownloadHelper(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PixivDownloadHelperClass())
{
    ui->setupUi(this);
    if (_backgroundPicturePath == _EMPTY_STRING) {
        image.fill(Qt::transparent);
        pix.fill(Qt::transparent);
    }
    else {
        //加载背景图片
        image.load(_backgroundPicturePath.c_str());
        pix = pix.fromImage(image);
        //背景图片缩放
        temp = pix;
        temp = pix.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    }
    this->imageWidth = temp.width();
    this->imageHeight = temp.height();
    //记录窗口大小
    wWidth = this->width();
    wHeight = this->height();
    //计算透明度
    opacity = (double)_windowTransparency / _windowTransparency_division;

    //初始化组件
    layout = new QGridLayout;
    menuWidget = new MenuWidget;
    pixivWidget = new PixivWidget;
    settingWidget = new SettingWidget;

    stackedWidget = new StackedWidget;

    //功能窗口加入窗口堆栈，索引返回到对应菜单按钮
    menuWidget->pixivButton->setIndex(stackedWidget->addWidget(pixivWidget));
    menuWidget->settingButton->setIndex(stackedWidget->addWidget(settingWidget));

    //信号槽实现切换窗口
    connect(menuWidget->pixivButton, &MenuButton::indexSignal, stackedWidget, &StackedWidget::switchWidget);
    connect(menuWidget->settingButton, &MenuButton::indexSignal, stackedWidget, &StackedWidget::switchWidget);
    //信号槽实现滑块改变背景透明度
    connect(settingWidget->subWidget->changeTransparencyWidget->slider, &QSlider::valueChanged,
        this, &PixivDownloadHelper::changeTransparency);
    //信号槽实现改变背景图片
    connect(settingWidget->subWidget->changeBackImageWidget, &ChangeBackgroundImageWidget::backgroundChanged,
        this, &PixivDownloadHelper::changeBackgroundImage);
    //切换窗口时重新计算下载项目窗口动态布局
    connect(this->stackedWidget, &QStackedWidget::currentChanged,
        this->pixivWidget->downloadWidget->itemWidget, &PixivDownloadItemWidget::caculateColumn);

    //鼠标进入右侧界面则折叠菜单界面
    connect(this->stackedWidget, &StackedWidget::enterSignal,
        this->menuWidget, &MenuWidget::widgetFold);

    //窗口加入布局
    layout->addWidget(menuWidget, 0, 0);
    layout->addWidget(stackedWidget, 0, 1);
    layout->setSpacing(_margin_width);
    layout->setMargin(_margin_width);

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
    //计算透明度
    opacity = (double)_windowTransparency / _windowTransparency_division;
    this->repaint();
    return;
}

void PixivDownloadHelper::changeBackgroundImage() {
    //重新加载新图片
    image.load(_backgroundPicturePath.c_str());
    pix = pix.fromImage(image);

    //拉伸新图片适应窗口大小
    this->stretchImage();
    //调用重绘
    this->repaint();
    return;
}

void PixivDownloadHelper::stretchImage() {
    temp = pix;
    if (!pix.isNull()) {
        //保持横纵比缩放图片适应窗口大小
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
    }
    return;
}

void PixivDownloadHelper::paintEvent(QPaintEvent* paintE) {
    //设置背景
    QPainter painter(this);
    //设置背景图片不透明度
    painter.setOpacity(opacity);
    //在窗口中心绘制图片
    painter.drawPixmap(xpos, ypos, temp);
}

void PixivDownloadHelper::resizeEvent(QResizeEvent* event) {
    //缩放图像
    this->stretchImage();
    //调用重绘
    this->repaint();
}