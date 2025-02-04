#include "BasicButton.h"

// AnimationButton
AnimationButton::AnimationButton(const QString& text, const QString& icon, const QSize& size, const size_t borderRadius)
    : borderRadius(borderRadius) {
    // 初始化组件
    iconLabel = new QLabel();
    textLabel = new QLabel();
    layout = new QHBoxLayout();
    hoverAnimation = std::make_unique<QPropertyAnimation>(this, "color");

    // 设置颜色
    buttonColor = BUTTON_COLOR_NORMAL;

#if defined(__APPLE__)
    setAttribute(Qt::WA_LayoutUsesWidgetRect);
#endif

    // 设置样式
    setStyleSheet("QPushButton:hover { border: none; }");

    // 大小设置
    this->resize(size);

    // 设置动画
    hoverAnimation->setDuration(200);
    hoverAnimation->setEasingCurve(QEasingCurve::OutCubic);

    // 设置文字
    this->textLabel->setText(tr(text.toStdString().c_str()));
    this->textLabel->setFont(QFont("Microsoft YaHei", 9, 50)); // 设置字体：微软雅黑

    // 设置图标
    if (icon != EMPTY_STRING) {
        QIcon ico(icon);
        QPixmap pix = ico.pixmap(
            QSize(std::min(this->height(), this->width() * 3 / 4), std::min(this->height(), this->width() * 3 / 4)));
        this->iconLabel->setPixmap(pix);
    }

    // 布局管理
    layout->setAlignment(Qt::AlignCenter);
    if (icon != EMPTY_STRING && text != EMPTY_STRING) {
        // 同时具有图标和文字标签
        layout->addSpacing(this->width() / 20);
        layout->addWidget(iconLabel);
        layout->addSpacing(this->width() / 30);
        layout->addWidget(textLabel);
        layout->setAlignment(Qt::AlignLeft);
    } else if (icon != EMPTY_STRING) {
        // 只有图标
        layout->addWidget(iconLabel);
    } else if (text != EMPTY_STRING) {
        // 只有文字标签
        layout->addWidget(textLabel);
    }
    layout->setMargin(0);

    this->setLayout(layout);
}

void AnimationButton::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(buttonColor); // 按钮颜色
    if (isChecked()) {
        painter.setBrush(BUTTON_COLOR_PRESSED);
    }

    QRect rt = this->rect();
    rt.setWidth(rt.width());
    rt.setHeight(rt.height());
    painter.drawRoundedRect(rt, borderRadius, borderRadius); // 绘制圆角
}

void AnimationButton::enterEvent(QEvent* event) {
    setFocus(); // 设为焦点
    hoverAnimation->stop();
    hoverAnimation->setStartValue(this->color());
    hoverAnimation->setEndValue(BUTTON_COLOR_HOVER);
    hoverAnimation->start();
}

void AnimationButton::leaveEvent(QEvent* event) {
    clearFocus(); // 清除焦点

    hoverAnimation->stop();
    hoverAnimation->setStartValue(this->color());
    hoverAnimation->setEndValue(BUTTON_COLOR_NORMAL);
    hoverAnimation->start();
}

void AnimationButton::mousePressEvent(QMouseEvent* e) {
    hoverAnimation->stop();
    hoverAnimation->setStartValue(this->color());
    hoverAnimation->setEndValue(BUTTON_COLOR_PRESSED);
    hoverAnimation->start();
}

void AnimationButton::mouseReleaseEvent(QMouseEvent* e) {
    hoverAnimation->stop();
    hoverAnimation->setStartValue(this->color());
    hoverAnimation->setEndValue(BUTTON_COLOR_HOVER);
    hoverAnimation->start();
    emit click();
}

// MenuButton
MenuButton::MenuButton(const QString& label, const QString& icon, const QSize& size, const size_t borderRadius)
    : AnimationButton(label, icon, size, borderRadius) {
    // 设置大小
    setFixedSize(MENU_BUTTON_SIZE);

    setAutoExclusive(true); // 设置互斥
    setCheckable(true);
    setFont(QFont("Microsoft YaHei")); // 设置字体：微软雅黑
}

void MenuButton::setIndex(int id) {
    this->index = id;
}

int MenuButton::getIndex() {
    return this->index;
}

// TranslucentLineEdit
TranslucentLineEdit::TranslucentLineEdit() {
    setFrame(false); // 无边框
    this->setStyleSheet("border-radius:5px;"
                        "background-color:rgba(255,255,255,0.4);"); // 样式表设置圆角和背景色
    setFont(QFont("Microsoft YaHei", 8, 50));                       // 设置字体：微软雅黑
}

// PixivUrlEdit
PixivUrlEdit::PixivUrlEdit() {
    // PixivUrlEdit文本框设置
    setFixedHeight(PIXIV_URL_EDITOR_SIZE.height());                 // 设置高度
    setPlaceholderText("https://www.pixiv.net/artworks/XXXXXXXXX"); // 背景提示

    connect(QApplication::clipboard(), &QClipboard::dataChanged, this, [this]() {
        if (QApplication::clipboard()->text() != this->text()) {
            this->clear();                                    // 清理文本框
            this->setText(QApplication::clipboard()->text()); // 将剪切板内容读取到文本框
            emit returnPressed();
        }
    });
}

// TransparentTextEdit
TransparentTextEdit::TransparentTextEdit() {
    setFrameStyle(NoFrame); // 无边框

    // 关闭水平滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 初始化滚动动画
    verticalScrollAnimation = std::make_unique<QPropertyAnimation>(this->verticalScrollBar(), "value");
    verticalScrollAnimation->setDuration(100);
    verticalScrollAnimation->setEasingCurve(QEasingCurve::OutCubic);

    this->setStyleSheet("background-color:rgba(255,255,255,0);");

    std::string styleSheet = ("QScrollBar:vertical{"
                              "background-color:transparent;"
                              "width:" +
                              std::to_string(SCROLLER_BAR_WIDTH) +
                              "px;"
                              "}"
                              "QScrollBar:handle:vertical{"
                              "background:" +
                              getSheetColor(SCROLLER_BAR_COLOR_NORMAL) +
                              ";"
                              "border-radius:" +
                              std::to_string(SCROLLER_BAR_WIDTH / 2) +
                              "px;"
                              "}"
                              "QScrollBar:handle:vertical:hover{"
                              "background:" +
                              getSheetColor(SCROLLER_BAR_COLOR_HOVER) +
                              ";"
                              "border-radius:" +
                              std::to_string(SCROLLER_BAR_WIDTH / 2) +
                              "px;"
                              "}"
                              "QScrollBar:add-page:vertical{"
                              "background-color:transparent;"
                              "}"
                              "QScrollBar:sub-page:vertical{"
                              "background-color:transparent;"
                              "}"
                              "QScrollBar:sub-line:vertical{"
                              "background:none;"
                              "border:none;"
                              "color:none;"
                              "}"
                              "QScrollBar:add-line:vertical{"
                              "background:none;"
                              "border:none;"
                              "color:none;"
                              "}");

    this->verticalScrollBar()->setStyleSheet(QString::fromStdString(styleSheet));

    setFont(QFont("Microsoft YaHei", 8, 50)); // 设置字体：微软雅黑
    // setAlignment(Qt::AlignLeft);//靠左显示
}

void TransparentTextEdit::wheelEvent(QWheelEvent* wheelEvent) {
    if (wheelEvent->source() == Qt::MouseEventNotSynthesized) {
        verticalScrollAnimation->stop();
        verticalScrollAnimation->setEndValue(this->verticalScrollBar()->value() - wheelEvent->pixelDelta().y() / 20);
        verticalScrollAnimation->start();
        wheelEvent->accept();
    } else {
        QPlainTextEdit::wheelEvent(wheelEvent);
        wheelEvent->accept();
    }
}

// TextLabel
TextLabel::TextLabel() {
    setMinimumSize(SETTING_TITLE_LABEL_SIZE);  // 设置最小大小
    setFont(QFont("Microsoft YaHei", 10, 50)); // 设置字体：微软雅黑
    setAlignment(Qt::AlignLeft);               // 靠左显示
}

// Slider
void Slider::wheelEvent(QWheelEvent* wheelE) {
}