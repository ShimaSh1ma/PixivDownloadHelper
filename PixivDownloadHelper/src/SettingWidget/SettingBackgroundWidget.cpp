#include "SettingWidget/SettingBackgroundWidget.h"

#include <QtWidgets/qfiledialog.h>

#include "InitFunctions.h"

// SettingBackgroundWidget
SettingBackgroundWidget::SettingBackgroundWidget() {
    // 初始化组件
    layout = new QGridLayout;
    title = new TextLabel;
    imageView = new QLabel;
    changeButton = new AnimationButton(tr("Change"));
    removeButton = new AnimationButton(tr("Remove"));

    // 按钮大小设置
    changeButton->setFixedSize(PIXIV_DOWNLOAD_BUTTON_SIZE);
    removeButton->setFixedSize(PIXIV_DOWNLOAD_BUTTON_SIZE);
    // 标题标签设置
    title->setText(tr("Change Background"));
    // 缩略图窗口设置
    imageView->setFixedSize(SETTING_BG_PREVIEW_SIZE); // 设置缩略图窗口大小
    QPixmap pix(_backgroundPicturePath.c_str());      // 加载图片
    imageView->setPixmap(pix.scaled(imageView->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)); // 缩放适应大小

    // 信号与槽连接
    connect(this->changeButton, &AnimationButton::clicked, this,
            &SettingBackgroundWidget::chooseImage); // 按下切换按钮，选择背景图片
    connect(this->removeButton, &AnimationButton::clicked, this,
            &SettingBackgroundWidget::removeImage); // 按下移除按钮移除背景图片

    // 布局管理
    layout->addWidget(title, 0, 0, 1, 2);
    layout->addWidget(imageView, 1, 0, 5, 2);
    layout->addWidget(changeButton, 2, 1);
    layout->addWidget(removeButton, 4, 1);

    this->setLayout(layout);
}

void SettingBackgroundWidget::chooseImage() {
    // 打开文件资源管理器
    std::string temp = QFileDialog::getOpenFileName(NULL, "Background", "./", "Image(*.png *.jpg)").toStdString();

    if (temp != "") {
        // 打开文件资源管理器选择背景图片路径
        _backgroundPicturePath = temp;
        // 缩略图窗口加载选择好的背景图片
        QPixmap pix(_backgroundPicturePath.c_str());
        imageView->setPixmap(pix.scaled(imageView->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        // 更新设置文件
        changeBackgroundImagePath();
        // 发送背景图片更改信号，供主窗口刷新
        emit backgroundImgChanged();
    }
}

void SettingBackgroundWidget::removeImage() {
    // 背景路径置空
    _backgroundPicturePath = EMPTY_STRING;
    // 清楚缩略图显示
    imageView->clear();
    // 更新设置文件
    changeBackgroundImagePath();
    // 通知主窗口刷新
    emit backgroundImgChanged();
}
