#include "PixivWidget/PixivUrlWidget.h"

// PixivUrlWidget
PixivUrlWidget::PixivUrlWidget() : TranslucentWidget() {
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