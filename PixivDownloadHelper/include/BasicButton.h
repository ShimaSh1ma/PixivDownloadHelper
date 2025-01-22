#pragma once

/* 定义基本的组件样式类 */
#include <QtCore/qpropertyanimation.h>
#include <QtGui/qclipboard.h>
#include <QtGui/qevent.h>
#include <QtGui/qpainter.h>
#include <QtGui/qscreen.h>
#include <QtGui/qwindow.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qplaintextedit.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qscrollbar.h>
#include <QtWidgets/qscroller.h>
#include <QtWidgets/qslider.h>
#include <QtWidgets/qtextedit.h>

#include "GuiConstant.h"

/* 按钮样式 */
// 动画按钮
class AnimationButton : public QPushButton {
    Q_OBJECT;

    Q_PROPERTY(QColor color READ color WRITE setColor);

  public:
    explicit AnimationButton(const QString& text = nullptr, const QString& icon = nullptr,
                             const QSize& size = QSize(0, 0), const size_t borderRadius = 9);
    ~AnimationButton() = default;

    AnimationButton(const AnimationButton&) = delete;
    AnimationButton& operator=(const AnimationButton&) = delete;
    AnimationButton(AnimationButton&&) = delete;
    AnimationButton& operator=(AnimationButton&&) = delete;

  private:
    QColor buttonColor;                                 // 按钮颜色
    QLabel* iconLabel;                                  // 图标标签
    QLabel* textLabel;                                  // 文字标签
    QHBoxLayout* layout;                                // 水平布局
    std::unique_ptr<QPropertyAnimation> hoverAnimation; // 鼠标进入动画

    inline QColor color() {
        return this->buttonColor;
    } // 获取按钮颜色
    inline void setColor(const QColor& color) {
        this->buttonColor = color;
        repaint();
    }
    size_t borderRadius;

  protected:
    virtual void paintEvent(QPaintEvent* event) override;    // 重写绘制事件
    virtual void enterEvent(QEvent* event) override;         // 重写鼠标进入事件
    virtual void leaveEvent(QEvent* event) override;         // 重写鼠标离开事件
    virtual void mousePressEvent(QMouseEvent* e) override;   // 重写鼠标按下事件
    virtual void mouseReleaseEvent(QMouseEvent* e) override; // 重写鼠标释放事件
};

// 主菜单按钮，互斥
class MenuButton : public AnimationButton {
    Q_OBJECT
  public:
    explicit MenuButton(const QString& label = nullptr, const QString& icon = nullptr,
                        const QSize& size = MENU_BUTTON_SIZE, const size_t borderRadius = 6);
    ~MenuButton() = default;

    MenuButton(const MenuButton&) = delete;
    MenuButton& operator=(const MenuButton&) = delete;
    MenuButton(MenuButton&&) = delete;
    MenuButton& operator=(MenuButton&&) = delete;

    void setIndex(int id); // 传入对应窗口索引
    int getIndex();

  private:
    int index = 0; // 按钮对应窗口索引
};

/* 单行文本框样式 */
// 半透明圆角文本框
class TranslucentLineEdit : public QLineEdit {
  public:
    explicit TranslucentLineEdit();
    ~TranslucentLineEdit() = default;

  private:
};

// pixiv url输入文本框
class PixivUrlEdit : public TranslucentLineEdit {
  public:
    explicit PixivUrlEdit();
    ~PixivUrlEdit() = default;

  private:
};

// 显示下载路径文本框
class DirEdit : public TranslucentLineEdit {
  public:
    DirEdit() = default;
    ~DirEdit() = default;
};

/* 文本编辑框 */
// 透明多行文本框
class TransparentTextEdit : public QPlainTextEdit {
  public:
    explicit TransparentTextEdit();
    ~TransparentTextEdit() = default;

  private:
    std::unique_ptr<QPropertyAnimation> verticalScrollAnimation;
    std::unique_ptr<QPropertyAnimation> horizontalScrollAnimation;

  protected:
    virtual void wheelEvent(QWheelEvent* wheelEvent) override; // 滚轮实现平滑动画
};

/* 自定义标签 */
// 文字标签
class TextLabel : public QLabel {
  public:
    explicit TextLabel();
    ~TextLabel() = default;

  private:
};

/* 滚动条 */
class Slider : public QSlider {
  protected:
    void wheelEvent(QWheelEvent* wheelE) override;
};