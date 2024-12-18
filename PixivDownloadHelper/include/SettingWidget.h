#pragma once

/* 定义用户设置窗口 */
#include "GuiConstant.h"
#include "InitFunctions.h"
#include "BasicWidget.h"
#include "BasicButton.h"

#include <QtWidgets/qscrollbar.h>
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlayout.h>

/*
    切换下载路径子窗口，具有一个显示路径的文本框，
    和一个切换路径按钮，切换路径按钮打开文件资源管理器选择路径
*/
class ChangeDownloadPathWidget :
    public TranslucentWidget
{
    Q_OBJECT
public:
    explicit ChangeDownloadPathWidget();
    ~ChangeDownloadPathWidget();
public slots:
    void chooseDownloadPath();//打开文件资源管理器选择下载路径，并将更改后的路径写入downloadPath.cfg文件
private:
    TextLabel* title;
    //路径显示栏
    DirEdit* pathEdit;
    //路径切换按钮
    AnimationButton* changeButton;

    //网格布局
    QGridLayout* layout;
};

class ChangePixivCookieWidget ://更改PixivCookie的窗口
    public TranslucentWidget
{
    Q_OBJECT
public:
    explicit ChangePixivCookieWidget();
    ~ChangePixivCookieWidget();
public slots:
    void saveCookie();//更改_pixivCookie,并设置pixiv cookie文本框为只读
    void turnEditable();//设置pixiv cookie文本框可编辑
private:
    //标题标签
    TextLabel* title;
    //显示当前cookie的文本框
    TransparentTextEdit* textEdit;
    //更改按钮
    AnimationButton* changeButton;
    //保存更改按键
    AnimationButton* saveButton;

    //网格布局
    QGridLayout* layout;

    bool showOrNot{ false };//窗口显示或隐藏状态位
protected:
    virtual void mousePressEvent(QMouseEvent* mouseE) override;//重写鼠标点击事件，实现窗口显示或隐藏
};

class ChangeTransparencyWidget ://更改背景图片透明度的窗口
    public TranslucentWidget
{
    Q_OBJECT
public:
    explicit ChangeTransparencyWidget();
    ~ChangeTransparencyWidget() = default;
public slots:
    void saveTranparency();//保存透明度设置
signals:
    void sliderValueChange(int value);
private:
    //标题标签
    TextLabel* title;
    //滑动条
    Slider* slider;
    //网格布局
    QGridLayout* layout;
};

class ChangeBackgroundImageWidget ://更改背景图片的窗口
    public TranslucentWidget
{
    Q_OBJECT
public:
    explicit ChangeBackgroundImageWidget();
    ~ChangeBackgroundImageWidget();
public slots:
    void chooseImage();//打开资源管理器并选择背景图片，更新背景图片设置文件backgroundPicture.cfg
    void removeImage();//移除背景图片
signals:
    void backgroundImgChanged();//发送背景Í改变信号通知主窗口刷新
private:
    TextLabel* title;
    //背景图片预览窗口
    QLabel* imageView;
    //按钮
    AnimationButton* changeButton;//切换按钮
    AnimationButton* removeButton;//移除按钮

    //网格布局
    QGridLayout* layout;
};

class SubSettingWidget ://用户设置窗口
    public TransparentWidget
{
    Q_OBJECT
public:
    explicit SubSettingWidget();//构造函数
    ~SubSettingWidget();//析构函数
signals:
    void changeTransparencySliderValueChange(int value);
    void backgroundImgChanged();
private:
    //切换下载路径子窗口
    ChangeDownloadPathWidget* changeDirWidget;

    //更改pixiv cookie子窗口
    ChangePixivCookieWidget* changePixivCookieWidget;

    //更改背景透明度子窗口
    ChangeTransparencyWidget* changeTransparencyWidget;

    //更改背景图片子窗口
    ChangeBackgroundImageWidget* changeBackImageWidget;

    //垂直布局
    QVBoxLayout* layout;
};

class SettingWidget ://用户设置窗口（添加滚动）
    public TransparentWidget
{
    Q_OBJECT
public:
    explicit SettingWidget();
    ~SettingWidget() = default;
signals:
    void changeTransparencySliderValueChange(int value);
    void backgroundImgChanged();
private:
    //窗口内容
    SubSettingWidget* subWidget;
    //作为容器提供滚动条
    TransparentScrollArea* scrollArea;

    //加入布局自适应窗口大小
    QVBoxLayout* layout;
};
