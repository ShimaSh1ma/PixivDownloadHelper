#pragma once

/* 定义图形界面布局常量
   如：窗口大小、窗口位置、窗口颜色、背景图片路径
   、按钮大小、按钮位置等
*/

#include <QtGui/qcolor.h>
#include <QtCore/qsize.h>

#include <string>

inline std::string getSheetColor(const QColor& color) {
   return std::string("rgba(") +
      std::to_string(color.red()) +
      std::string(",") +
      std::to_string(color.green()) +
      std::string(",") +
      std::to_string(color.blue()) +
      std::string(",") +
      std::to_string(color.alpha()) +
      std::string(")");
}

//用户设置（config）信息
extern std::string _backgroundPicturePath;//背景图片路径
extern std::string _downloadPath;//下载根目录
extern std::string _pixivCookie;//pixivcookie字符串
extern size_t _windowTransparency;//背景图片透明度

constexpr const char* CONFIG_FILE_SAVE_PATH = "./config/downloadPath.cfg";//下载根目录设置文件路径
constexpr const char* CONFIG_PIXIV_COOMKIE_PATH = "./config/pixivCookie.cfg";//pixivcookie存放文件路径
constexpr const char* CONFIG_BG_PIC_PATH = "./config/backgroundPicture.cfg";//背景文件config保存路径
constexpr const char* CONFIG_WINDOW_TRANSPARENCY_PATH = "./config/windowTransparency.cfg";//背景透明度config保存路径
constexpr const char* CONFIG_UNDONE_PATH = "./config/downloadData.cfg";//保存用户未完成的下载项目信息

//未获取到缩略图时的默认缩略图路径
constexpr const char* DEFAULT_PREVIEW_PATH = ":/image/defaultPreview";//默认预览图路径

//程序图标路径
constexpr const char* ICON_PROGRAM_MAIN = ":/icon/mainIcon";//程序图标路径
constexpr const char* ICON_FOLD = ":/icon/fold";//折叠图标路径
constexpr const char* ICON_UNFOLD = ":/icon/unfold";//展开图标路径
constexpr const char* ICON_PIXIV = ":/icon/pixiv";//展开图标路径
constexpr const char* ICON_SETTING = ":/icon/setting";//设置图标路径
constexpr const char* ICON_EXTENT = ":/icon/extend";//扩展图标路径

//正则匹配规则表达式
constexpr const char* REGEX_PIXIV_ILLUST = "https://i.pximg.net/img-original[^\"]+";					//pixiv单个作品中的图片  url匹配规则
constexpr const char* REGEX_PIXIV_ARTWORK = "https://www.pixiv.net/artworks/[\\d]{8,9}";                  //pixiv单个作品  url匹配规则
constexpr const char* REGEX_PIXIV_USER_ALL = "https://www.pixiv.net/users/([\\d]{1,8})(?:/artworks)?";                  //pixiv一个用户所有作品  url匹配规则
constexpr const char* REGEX_PIXIV_USER_TAGGED = "https://www.pixiv.net/users/([\\d]{1,8})/(?:artworks|illustrations)/(.+)?";               //pixiv一个用户筛选后作品  url匹配规则
constexpr const char* REGEX_TELEGRAM = "https://telegra.ph/[\\S]+";                       //telegram匹配规则

constexpr const char* EMPTY_STRING = "";

//下载状态枚举量
enum class downloadState {
   WAITING,
   DOWNLOADING,
   SUCCESS,
   HTTPREQUESTFAILED
};

//统一边框宽度
constexpr size_t MARGIN_WIDTH = 14;

//滑动条宽度
constexpr size_t SCROLLER_BAR_WIDTH = 10;
//滚动条颜色
constexpr QColor SCROLLER_BAR_COLOR_NORMAL{ 220,220,220,255 };
constexpr QColor SCROLLER_BAR_COLOR_HOVER{ 200,200,200,255 };

//pixiv窗口ui尺寸
constexpr QSize PIXIV_URL_EDITOR_SIZE{ 160,30 };//url输入文本框最小大小
constexpr QSize PIXIV_DOWNLOAD_BUTTON_SIZE{ 80,PIXIV_URL_EDITOR_SIZE.height() };//pixiv下载按钮大小
constexpr QSize PIXIV_URL_WIDGET_SIZE{ 2 * PIXIV_URL_EDITOR_SIZE.width() + 2 * MARGIN_WIDTH,
                PIXIV_URL_EDITOR_SIZE.height() + 2 * MARGIN_WIDTH };//pixiv url输入窗口大小
constexpr size_t PIXIV_DOWNLOAD_TITLE_WIDGET_HEIGHT{ 20 };//pixiv下载项目url标题窗口高度
constexpr size_t PIXIV_DOWNLOAD_STATE_HEIGHT{ 20 };//pixiv下载项目下载状态窗口高度
constexpr size_t PIXIV_DOWNLOAD_ITEM_WITHOUT_PIC_HEIGHT{ PIXIV_DOWNLOAD_TITLE_WIDGET_HEIGHT +
                 PIXIV_DOWNLOAD_STATE_HEIGHT + 3 * MARGIN_WIDTH };//pixiv下载项目无缩略图高度
constexpr QSize PIXIV_PREVIEW_SIZE{ 220,220 };//pixiv下载缩略图大小
constexpr QSize PIXIV_DOWNLOAD_FOLD_BUTTON_SIZE{ 32,32 };//pixiv上方窗口隐藏显示缩略图按钮大小
constexpr size_t PIXIV_DOWNLOAD_ITEM_WITH_PIC_HEIGHT{ PIXIV_DOWNLOAD_ITEM_WITHOUT_PIC_HEIGHT +
                 PIXIV_PREVIEW_SIZE.height() + 2 * MARGIN_WIDTH };//pixiv单个下载项目有缩略图高度
constexpr size_t PIXIV_DOWNLOAD_ITEM_MIN_WIDTH{ PIXIV_URL_WIDGET_SIZE.width() - MARGIN_WIDTH };//pixiv下载项目最小宽度
constexpr size_t PIXIV_DOWNLOAD_ITEM_MAX_WIDTH{ PIXIV_DOWNLOAD_ITEM_MIN_WIDTH * 2 };//pixiv下载项目最大宽度

//设置窗口ui尺寸
constexpr QSize SETTING_PATH_EDITOR_SIZE = PIXIV_URL_EDITOR_SIZE;//显示下载路径文本框大小
constexpr QSize SETTING_BG_PREVIEW_SIZE = { 200,200 };//背景缩略图预览窗口大小
constexpr QSize SETTING_COOKIE_EDITOR_SIZE = { 100,150 };//修改pixiv cookie的文本框大小
constexpr QSize SETTING_TITLE_LABEL_SIZE = { 50,20 };//设置窗口标题栏大小

//主菜单窗口ui尺寸
constexpr QSize MENU_BUTTON_SIZE{ 108,32 };//主菜单按钮最大大小
constexpr QSize MENU_EXTENT_BUTTON_SIZE{ 18,48 };//展开按钮大小大小
constexpr size_t MENU_BUTTON_COUNT{ 2 };//主菜单按钮数量
constexpr size_t MENU_WIDGET_UNFOLD_WIDTH{ MENU_BUTTON_SIZE.width() };//主菜单窗口最大宽度
constexpr size_t MENU_WIDGET_FOLD_WIDTH{ MENU_EXTENT_BUTTON_SIZE.width() };//主菜单窗口最小宽度

//窗口颜色
constexpr QColor WIDGET_NON_TRANSPARENT_COLOR{ 255,255,255,255 };//不透明窗口颜色
constexpr QColor WIDGET_TRANSLUCENT_COLOR{ 255,255,255,150 };//半透明窗口颜色
constexpr QColor WIDGET_HOVER_COLOR{ 165,226,255,150 };//鼠标悬浮时窗口颜色
constexpr QColor WIDGET_TRANSPARENT_COLOR{ 255,255,255,0 };//透明窗口颜色

//按钮颜色
constexpr QColor BUTTON_COLOR_NORMAL{ 230,230,230,150 };//按钮平常颜色
constexpr QColor BUTTON_COLOR_HOVER{ 165,208,255,150 };//按钮悬停颜色
constexpr QColor BUTTON_COLOR_PRESSED{ 165,208,255,180 };//按钮按下颜色

constexpr size_t WINDOW_TRANSPARENCY_DIVISION = 255;//背景透明度分度值