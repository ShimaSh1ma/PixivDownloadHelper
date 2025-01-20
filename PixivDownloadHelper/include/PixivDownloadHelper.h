#pragma once

#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include <QtWidgets/qopenglwidget.h>

#include "MenuWidget.h"
#include "PixivWidget/PixivWidget.h"
#include "SettingWidget.h"

/*  主界面窗口  */
class PixivDownloadHelper : public QWidget {
    Q_OBJECT
  public:
    PixivDownloadHelper(QWidget* parent = nullptr);
    ~PixivDownloadHelper() = default;

  public slots:
    // 响应改变不透明度的滑块产生的valueChanged信号改变窗口透明度，调用一次repaint()
    void changeTransparency(int transparency);
    // 响应改变背景图片产生的valueChanged信号改变背景图片，调用一次repaint()
    void changeBackgroundImage();

  private:
    QHBoxLayout* layout; // 水平布局

    MenuWidget* menuWidget; // 界面切换按钮窗口

    PixivWidget* pixivWidget;     // pixiv下载窗口
    SettingWidget* settingWidget; // 设置窗口

    StackedWidget* stackedWidget; // 显示一个功能窗口，可以切换

    QImage image; // 背景图片
    QPixmap pix;  // 背景图片缩放
    QPixmap temp; // 临时背景缓冲

    double opacity; // 背景透明度

    // 图片大小记录，用作缓冲
    int imageWidth = 0;
    int imageHeight = 0;
    // 窗口大小记录，用作缓冲
    int wWidth = 0;
    int wHeight = 0;
    // 图片位置记录，用作缓冲
    int xpos = 0;
    int ypos = 0;

    void stretchImage(); // 拉伸背景图片大小，适应窗口变化
  protected:
    virtual void paintEvent(QPaintEvent* paintE) override;  // 重写paint事件，绘制背景图片
    virtual void resizeEvent(QResizeEvent* event) override; // 重写resize事件，缩放背景图片
    virtual void closeEvent(QCloseEvent* event) override;   // 关闭时间
};