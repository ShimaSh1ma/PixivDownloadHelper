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

const std::string _icon_main_path = ".\\resource\\icon\\main.ico";//程序图标路径
const std::string _icon_fold_path = ".\\resource\\icon\\ico_fold.png";//折叠图标路径
const std::string _icon_unfold_path = ".\\resource\\icon\\ico_unfold.png";//展开图标路径
const std::string _icon_pixiv_path = ".\\resource\\icon\\ico_pixiv.png";//展开图标路径
const std::string _icon_setting_path = ".\\resource\\icon\\ico_setting.png";//设置图标路径

const std::string _regex_pixiv_illust_url = "https://i.pximg.net/img-original[^\"]+";
const std::string _regex_pixiv_artwork_url = "https://www.pixiv.net/artworks/[\\d]{8,9}";
const std::string _regex_pixiv_userAll_url = "https://www.pixiv.net/users/([\\d]{1,8})/artworks";
const std::string _regex_pixiv_userTagged_url = "https://www.pixiv.net/users/([\\d]{1,8})/artworks/(.+)?";