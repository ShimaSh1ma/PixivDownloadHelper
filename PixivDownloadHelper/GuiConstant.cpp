#include "GuiConstant.h"

std::string _downloadPath{};
std::string _pixivCookie{};
std::string _backgroundPicturePath{};
int _windowTransparency{ 5 };

const std::string _config_download_save_path = ".\\config\\downloadPath.cfg";//下载根目录设置文件路径
const std::string _config_pixivcookie_save_path = ".\\config\\pixivCookie.cfg";//pixivcookie存放文件路径
const std::string _config_background_picture_path=".\\config\\backgroundPicture.cfg";//背景文件config保存路径
const std::string _config_window_tranparency_path=".\\config\\windowTransparency.cfg";//背景透明度config保存路径

const std::string _default_preview_path = ".\\resource\\image\\defaultPreview";//默认预览图路径

const std::string _icon_path = ".\\resource\\icon\\main.ico";//程序图标路径

const std::string _regex_pixiv_rule = "https://i.pximg.net/img-original[^\"]+";
const std::string _pixiv_ajax = "https://www.pixiv.net/ajax/illust/";