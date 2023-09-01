#ifndef _PixivDownloadHelper
#define _PixivDownloadHelper

#include <QtWidgets/QWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/qopenglwidget.h>

#include "ui_PixivDownloadHelper.h"
#include "MenuWidget.h"
#include "PixivWidget.h"
#include "SettingWidget.h"
/*  主界面窗口  */
QT_BEGIN_NAMESPACE
namespace Ui { class PixivDownloadHelperClass; };
QT_END_NAMESPACE

class PixivDownloadHelper : public QWidget
{
    Q_OBJECT

public:
    QGridLayout* layout;//水平布局

    MenuWidget* menuWidget;//界面切换按钮窗口

    //功能窗口
    PixivWidget* pixivWidget;//pixiv下载窗口
    SettingWidget* settingWidget;//设置窗口

    QStackedWidget* stackedWidget;//显示一个功能窗口，可以切换

    PixivDownloadHelper(QWidget *parent = nullptr);
    ~PixivDownloadHelper();

public slots:
    //响应改变不透明度的滑块产生的valueChanged信号改变窗口透明度，调用一次repaint()
    void changeTransparency(int transparency);
    //响应改变背景图片产生的valueChanged信号改变背景图片，调用一次repaint()
    void changeBackgroundImage();
private:
    Ui::PixivDownloadHelperClass *ui;

    QImage image;//背景图片
    QPixmap pix;//背景图片缩放
    QPixmap temp;//临时背景缓冲

    //记录窗口大小，作为缓冲提升性能
    int WWidth{};
    int WHeight{};

    virtual void paintEvent(QPaintEvent* paintE);//重写paint事件，绘制背景图片
};

#endif