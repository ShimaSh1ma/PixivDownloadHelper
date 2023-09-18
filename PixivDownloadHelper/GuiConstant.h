#pragma once
/* 定义图形界面布局常量 
   如：窗口大小、窗口位置、窗口颜色、背景图片路径
   、按钮大小、按钮位置等*/

#include <QtGui/qcolor.h>
#include <QtCore/qsize.h>
#include <string>
//用户设置（config）信息
extern std::string _backgroundPicturePath;//背景图片路径
extern int _windowTransparency;//背景图片透明度
extern std::string _downloadPath;//下载根目录
extern std::string _pixivCookie;//pixivcookie字符串

//config文件保存路径
extern const std::string _config_download_save_path;//下载根目录condig保存路径
extern const std::string _config_pixivcookie_save_path;//pixivcookie config保存路径
extern const std::string _config_background_picture_path;//背景文件config保存路径
extern const std::string _config_window_tranparency_path;//背景透明度config保存路径

//未获取到缩略图时的默认缩略图路径
extern const std::string _default_preview_path;

//程序图标路径
extern const std::string _icon_main_path;
extern const std::string _icon_fold_path;//折叠图标路径
extern const std::string _icon_unfold_path;//展开图标路径
extern const std::string _icon_pixiv_path;//pixiv图标路径
extern const std::string _icon_setting_path;//设置图标路径
extern const std::string _icon_extend_path;//扩展图标路径

//——————————————正则匹配规则表达式—————————————————
extern const std::string _regex_pixiv_illust_url;					//pixiv单个作品中的图片  url匹配规则
extern const std::string _regex_pixiv_artwork_url;                  //pixiv单个作品  url匹配规则
extern const std::string _regex_pixiv_userAll_url;                  //pixiv一个用户所有作品  url匹配规则
extern const std::string _regex_pixiv_userTagged_url;               //pixiv一个用户筛选后作品  url匹配规则
//——————————————————————————————————————

//—————————————套接字缓冲区大小—————————————————
constexpr int _socket_buffer_size = 1024 * 4;
//——————————————————————————————————————

//——————————————异常检查宏常量定义———————————————
#define _M_WSASTART_ERR				"WSAStartup Error"			//winsock环境初始化异常
#define _M_DNS_ERR					"DNS Error"					//域名转换异常
#define _M_SOCKET_CREATE_ERR		"Socket Create Error"		//创建winsock套接字失败
#define _M_SOCKET_CONNECT_ERR		"Socket Connect Error"		//连接到服务器失败
#define _M_SOCKET_CLOSE_ERR			"Socket Close Error"		//关闭winsock套接字失败

#define _M_SSL_CONTEXT_ERR			"SSL_CTX_new Error"			//ssl上下文建立失败
#define _M_SSL_CREATE_ERR			"SSL New Error"				//ssl套接字创建失败
#define _M_SSL_CONNECT_ERR			"SSL Connect error"			//ssl握手失败
#define _M_SSL_WRITE_ERR			"SSL Write Error"			//ssl发送信息失败

#define _DOWNLOAD_ERR				"Download Error"			//下载文件失败
#define	_DOWNLOAD_SUCCESS			"Download Success"			//下载文件成功
#define _REQUEST_ERR				"Request Error"				//请求页面失败
#define _REQUEST_SUCCESS			"Request Success"			//请求页面成功

#define _FILE_OPEN_ERR				"Error Open "				//文件打开失败
#define _FILE_CREATE_ERR			"Error Create "				//文件创建失败

#define _EMPTY_STRING				""							//空字符串
//——————————————————————————————————————
enum class downloadState {
    WAITING,
    DOWNLOADING,
    SUCCESS,
    HTTPREQUESTFAILED
};//下载状态枚举量

//统一边框宽度
constexpr int _margin_width{ 10 };

//pixiv窗口ui尺寸
constexpr QSize _pixivUrlLineEdit_size{ 160,30 };//url输入文本框最小大小
constexpr QSize _toolButton_size{ 80,_pixivUrlLineEdit_size.height() };//pixiv下载按钮大小
constexpr QSize _pixivUrlWidget_size{ 2*_pixivUrlLineEdit_size.width() + 2 * _margin_width,
_pixivUrlLineEdit_size.height() + 2 * _margin_width };//pixiv url输入窗口大小
constexpr int _pixivDownloadItemTitle_height{ 20 };//pixiv下载项目url标题窗口高度
constexpr int _pixivDownloadItemState_height{ 20 };//pixiv下载项目下载状态窗口高度
constexpr int _pixivDownloadItemWithoutPre_height{ _pixivDownloadItemTitle_height +
_pixivDownloadItemState_height + 3 * _margin_width };//pixiv下载项目无缩略图高度
constexpr QSize _pixivDownloadItemPreviewImage_size{ 220,220 };//pixiv下载缩略图大小
constexpr QSize _pixivDownloadTopWidgetButton_size{ 32,32 };//pixiv上方窗口隐藏显示缩略图按钮大小
constexpr int _pixivDownloadItemWithPre_height{ _pixivDownloadItemWithoutPre_height +
_pixivDownloadItemPreviewImage_size.height() + 2 * _margin_width };//pixiv单个下载项目有缩略图高度
constexpr int _pixivDownloadItem_minWidth{ _pixivUrlWidget_size.width() - _margin_width };//pixiv下载项目最小宽度
constexpr int _pixivDownloadItem_maxWidth{ _pixivDownloadItem_minWidth * 2 };//pixiv下载项目最大宽度

//设置窗口ui尺寸
constexpr QSize _settingChangeDownloadPathLineEdit_size = _pixivUrlLineEdit_size;//显示下载路径文本框大小
constexpr QSize _settingChangeBackgroundLabel_size = { 200,200 };//背景缩略图预览窗口大小
constexpr QSize _settingChangePixivCookieTextEdit_size = { 100,150 };//修改pixiv cookie的文本框大小
constexpr QSize _settingTitleLabel_size = { 50,20 };//设置窗口标题栏大小

//主菜单窗口ui尺寸
constexpr QSize _menuButton_size{ 108,32 };//主菜单按钮最大大小
constexpr QSize _extendButton_size{ 18,48 };//展开按钮大小大小
constexpr int _menuButton_count = 2;//主菜单按钮数量
constexpr int _menuWidget_maxwidth{ _menuButton_size.width()};//主菜单窗口最大宽度
constexpr int _menuWidget_minwidth{ _extendButton_size.width()};//主菜单窗口最小宽度

//窗口颜色
constexpr QColor _nontransparentWidget_color{ 255,255,255,255 };//不透明窗口颜色
constexpr QColor _translucentWidget_color{ 255,255,255,150 };//半透明窗口颜色
constexpr QColor _transparentWidget_color{ 255,255,255,0 };//透明窗口颜色

//按钮颜色
constexpr QColor _buttonNormal_color{ 200,200,200,100 };//按钮平常颜色
constexpr QColor _buttonHover_color{ 180,180,180,150 };//按钮悬停颜色
constexpr QColor _buttonPressed_color{ 160,160,160,180 };//按钮按下颜色

constexpr int _windowTransparency_division = 255;//背景透明度分度值