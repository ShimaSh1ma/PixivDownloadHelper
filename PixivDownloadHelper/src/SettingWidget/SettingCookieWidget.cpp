#include "SettingWidget/SettingCookieWidget.h"

#include "InitFunctions.h"

// SettingCookieWidget
SettingCookieWidget::SettingCookieWidget() {
    // 初始化组件
    layout = new QGridLayout;
    textEdit = new TransparentTextEdit;
    changeButton = new AnimationButton(tr("Change"));
    saveButton = new AnimationButton(tr("Save"));
    title = new TextLabel;
    // 设置按钮大小
    changeButton->setFixedSize(PIXIV_DOWNLOAD_BUTTON_SIZE);
    saveButton->setFixedSize(PIXIV_DOWNLOAD_BUTTON_SIZE);
    // 标题设置
    title->setText(tr("Change Pixiv Cookie"));
    // 显示文本框设置
    textEdit->setMinimumSize(SETTING_COOKIE_EDITOR_SIZE);         // 设置最小大小
    textEdit->setPlainText(QString::fromStdString(_pixivCookie)); // 展示现在的cookie
    textEdit->setReadOnly(true); // 只读，在点击change按钮后可编辑,点击Save后恢复只读状态

    // 信号与槽连接
    connect(changeButton, &AnimationButton::clicked, this,
            &SettingCookieWidget::turnEditable); // 按下change按钮，编辑cookie
    connect(saveButton, &AnimationButton::clicked, this,
            &SettingCookieWidget::saveCookie); // 按下save按钮，保存cookie设置

    // 布局管理
    layout->addWidget(title, 0, 0);
    layout->addWidget(changeButton, 3, 1, 1, 1);
    layout->addWidget(saveButton, 3, 2, 1, 1);
    layout->addWidget(textEdit, 1, 0, 2, 3);
    // 文本框和修改按钮默认不可见
    this->textEdit->setVisible(false);
    this->changeButton->setVisible(false);
    this->saveButton->setVisible(false);

    this->setLayout(layout);
}

void SettingCookieWidget::saveCookie() {
    // 更改_pixivCookie
    _pixivCookie = this->textEdit->toPlainText().toStdString();
    // 设置为只读
    this->textEdit->setReadOnly(true);
    // 更新设置文件
    changePixivCookie();

    this->textEdit->setStyleSheet("background-color:rgba(255,255,255,0);");
}

void SettingCookieWidget::turnEditable() {
    this->textEdit->setReadOnly(false);
    this->textEdit->setStyleSheet("background-color:rgba(255,255,255,180);"
                                  "border-radius:8px;");
}

void SettingCookieWidget::mousePressEvent(QMouseEvent* mouseE) {
    if (mouseE->button() == Qt::LeftButton) { // 响应左键
        if (this->showOrNot) {
            this->textEdit->setVisible(false);
            this->changeButton->setVisible(false);
            this->saveButton->setVisible(false);
            this->showOrNot = false;
            return;
        } else {
            this->textEdit->setVisible(true);
            this->changeButton->setVisible(true);
            this->saveButton->setVisible(true);
            this->showOrNot = true;
            return;
        }
    }
}
