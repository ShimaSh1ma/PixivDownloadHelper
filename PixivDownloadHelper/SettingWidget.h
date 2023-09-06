#ifndef _SettingWidget
#define _SettingWidget

/* 定义用户设置窗口 */
#include "GuiConstant.h"
#include "InitFunctions.h"
#include "BasicWidget.h"
#include "BasicButton.h"
#include <qscrollbar.h>
#include <qfiledialog.h>
#include <qlabel.h>
#include <qlayout.h>
class ChangeDownloadPathWidget :/*切换下载路径子窗口，具有一个路径显示editline
                               和一个切换路径按钮，切换路径按钮打开文件资源管理器选择路径
                               */
    public TranslucentWidget
{
    Q_OBJECT
public:
    TextLabel* title;
    //路径显示栏
    DirEdit* pathEdit;
    //路径切换按钮
    ToolButton* changeButton;

    //网格布局
    QGridLayout* layout;

    ChangeDownloadPathWidget();
    ~ChangeDownloadPathWidget();
public slots:
    void chooseDownloadPath();//打开文件资源管理器选择下载路径，并将更改后的路径写入downloadPath.cfg文件
};

class ChangePixivCookieWidget ://更改PixivCookie的窗口
    public TranslucentWidget
{
    Q_OBJECT
public:
    //标题标签
    TextLabel* title;
    //显示当前cookie的文本框
    TransparentTextEdit* textEdit;
    //更改按钮
    ToolButton* changeButton;
    //保存更改按键
    ToolButton* saveButton;

    //网格布局
    QGridLayout* layout;

    ChangePixivCookieWidget();
    ~ChangePixivCookieWidget();
public slots:
    void saveCookie();//更改_pixivCookie,并设置pixiv cookie文本框为只读
    void turnEditable();//设置pixiv cookie文本框可编辑
private:
    bool showOrNot{ false };//窗口显示或隐藏状态位
protected:
    virtual void mousePressEvent(QMouseEvent* mouseE) override;//重写鼠标点击事件，实现窗口显示或隐藏
};

class ChangeTransparencyWidget ://更改背景图片透明度的窗口
    public TranslucentWidget
{
    Q_OBJECT
public:
    //标题标签
    TextLabel* title;
    //滑动条
    Slider* slider;
    //网格布局
    QGridLayout* layout;

    explicit ChangeTransparencyWidget();
    ~ChangeTransparencyWidget();
public slots:
    void saveTranparency();//保存透明度设置
private:
};

class ChangeBackgroundImageWidget ://更改背景图片的窗口
    public TranslucentWidget
{
    Q_OBJECT
public:
    TextLabel* title;
    //背景图片预览窗口
    QLabel* imageView;
    //切换按钮
    ToolButton* changeButton;
    //网格布局
    QGridLayout* layout;

    ChangeBackgroundImageWidget();
    ~ChangeBackgroundImageWidget();
public slots:
    void chooseImage();//打开资源管理器并选择背景图片，更新背景图片设置文件backgroundPicture.cfg
signals:
    void backgroundChanged();//发送背景改变信号通知主窗口刷新
};

class SubSettingWidget ://用户设置窗口
    public TransparentWidget
{
public:
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

    explicit SubSettingWidget();//构造函数
    ~SubSettingWidget();//析构函数
};

class SettingWidget ://用户设置窗口（添加滚动）
    public TransparentWidget
{
public:
    //窗口内容
    SubSettingWidget* subWidget;
    //作为容器提供滚动条
    TransparentScrollArea* scrollArea;

    //加入布局自适应窗口大小
    QVBoxLayout* layout;

    SettingWidget();
    ~SettingWidget();
private:
};

#endif