#include "SettingWidget/SettingWidget.h"

// SubSettingWidget
SubSettingWidget::SubSettingWidget() {
    // 组件初始化
    layout = new QVBoxLayout;
    changeDirWidget = new SettingTargetPathWidget;
    changePixivCookieWidget = new SettingCookieWidget;
    changeTransparencyWidget = new SettingTransparencyWidget;
    changeBackImageWidget = new SettingBackgroundWidget;

    connect(this->changeTransparencyWidget, &SettingTransparencyWidget::sliderValueChange, this,
            &SubSettingWidget::changeTransparencySliderValueChange);
    connect(this->changeBackImageWidget, &SettingBackgroundWidget::backgroundImgChanged, this,
            &SubSettingWidget::backgroundImgChanged);

    // 布局管理
    layout->addWidget(changeDirWidget);
    layout->addWidget(changePixivCookieWidget);
    layout->addWidget(changeTransparencyWidget);
    layout->addWidget(changeBackImageWidget);
    layout->addStretch(1);

    layout->setContentsMargins(0, 0, MARGIN_WIDTH - (MARGIN_WIDTH - SCROLLER_BAR_WIDTH) / 2, 0);

    setLayout(layout);
}

// SettingWidget
SettingWidget::SettingWidget() {
    // 初始化组件
    subWidget = new SubSettingWidget;
    scrollArea = new TransparentScrollArea;
    layout = new QVBoxLayout;

    connect(this->subWidget, &SubSettingWidget::changeTransparencySliderValueChange, this,
            &SettingWidget::changeTransparencySliderValueChange);

    connect(this->subWidget, &SubSettingWidget::backgroundImgChanged, this, &SettingWidget::backgroundImgChanged);

    // 设置滚动窗口
    scrollArea->setWidget(subWidget);     // 指定窗口
    scrollArea->setWidgetResizable(true); // 设置窗口可缩放
    scrollArea->setMinimumWidth(subWidget->minimumWidth());

    // 布局管理
    layout->addWidget(scrollArea);
    layout->setContentsMargins(0, 0, (MARGIN_WIDTH - SCROLLER_BAR_WIDTH) / 2, 0);

    this->setLayout(layout);
}