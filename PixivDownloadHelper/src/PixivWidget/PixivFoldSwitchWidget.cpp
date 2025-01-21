#include "PixivWidget/PixivFoldSwitchWidget.h"

// PixivFoldSwitchWidget
PixivFoldSwitchWidget::PixivFoldSwitchWidget() {
    // 组件按钮
    foldButton = new AnimationButton("", ICON_FOLD, PIXIV_DOWNLOAD_FOLD_BUTTON_SIZE, 4);
    unfoldButton = new AnimationButton("", ICON_UNFOLD, PIXIV_DOWNLOAD_FOLD_BUTTON_SIZE, 4);
    countLabel = new TextLabel();
    layout = new QHBoxLayout();

    // 设置按钮大小
    foldButton->setFixedSize(PIXIV_DOWNLOAD_FOLD_BUTTON_SIZE);
    unfoldButton->setFixedSize(PIXIV_DOWNLOAD_FOLD_BUTTON_SIZE);

    connect(this->foldButton, &QPushButton::clicked, this, &PixivFoldSwitchWidget::foldButtonClicked);
    connect(this->unfoldButton, &QPushButton::clicked, this, &PixivFoldSwitchWidget::unfoldButtonClicked);

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