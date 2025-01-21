#include "SettingWidget/SettingTargetPathWidget.h"

#include <QtWidgets/qfiledialog.h>

#include "InitFunctions.h"

// SettingTargetPathWidget
SettingTargetPathWidget::SettingTargetPathWidget() {
    // 组件初始化
    layout = new QGridLayout;

    title = new TextLabel;
    pathEdit = new DirEdit;
    changeButton = new AnimationButton(tr("Change Path"));
    // 设置按钮大小
    changeButton->setFixedSize(PIXIV_DOWNLOAD_BUTTON_SIZE);
    // 标题标签设置
    title->setText(tr("Change Download Path"));
    // 显示下载路径的文本框设置
    pathEdit->setReadOnly(true); // 只读
    pathEdit->setText(QString::fromStdString(_downloadPath));
    pathEdit->setFixedHeight(SETTING_PATH_EDITOR_SIZE.height());
    pathEdit->setMinimumWidth(SETTING_PATH_EDITOR_SIZE.width());

    // 信号与槽连接
    connect(this->changeButton, &AnimationButton::clicked, this,
            &SettingTargetPathWidget::chooseDownloadPath); // 按下change按钮改变下载路径

    // 布局管理
    layout->addWidget(title, 0, 0);
    layout->addWidget(pathEdit, 1, 0);
    layout->addWidget(changeButton, 1, 1);

    this->setLayout(layout);
}

void SettingTargetPathWidget::chooseDownloadPath() {
    // 打开文件资源管理器选择下载文件夹
    std::string temp = QFileDialog::getExistingDirectory(nullptr, nullptr, _downloadPath.c_str()).toStdString();

    if (temp != "") {
        _downloadPath = temp;
        // 更新下载路径显示
        this->pathEdit->setText(QString::fromStdString(_downloadPath));
        // 更改设置文件
        changeDownloadPath();
    }
}
