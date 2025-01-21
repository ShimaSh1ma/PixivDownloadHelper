#include "SettingWidget/SettingTransparencyWidget.h"

#include "InitFunctions.h"

// SettingTransparencyWidget
SettingTransparencyWidget::SettingTransparencyWidget() {
    // 组件初始化
    title = new TextLabel;
    slider = new Slider;
    layout = new QGridLayout;
    // 标题设置
    title->setText(tr("Change Window Transparency"));
    // 滑动条设置
    slider->setRange(0, WINDOW_TRANSPARENCY_DIVISION); // 设置范围
    slider->setValue(_windowTransparency);             // 设置默认值
    slider->setOrientation(Qt::Horizontal);            // 设为水平滚动条
    // 布局管理
    layout->addWidget(title, 0, 0);
    layout->addWidget(slider, 1, 0);

    // 信号与槽函数
    connect(this->slider, &QSlider::sliderReleased, this,
            &SettingTransparencyWidget::saveTranparency); // 释放滚动条时，保存透明度信息

    connect(this->slider, &QSlider::valueChanged, this, &SettingTransparencyWidget::sliderValueChange);

    this->setLayout(layout);
}

void SettingTransparencyWidget::saveTranparency() {
    // 保存透明度信息
    changeWindowTransparency();
}
