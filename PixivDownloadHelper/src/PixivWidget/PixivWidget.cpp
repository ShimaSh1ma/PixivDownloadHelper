#include "PixivWidget/PixivWidget.h"

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