#include "globalConstent.h"

//下载根目录设置文件路径
const std::string _config_download_save_path = ".\\config\\downloadDir.cfg";
//pixivcookie存放文件路径
extern const std::string _config_pixivcookie_save_path = ".\\config\\pixivCookie.cfg";

//下载根目录,默认路径E:\\qwq\\cos\\crawler
std::string _downloadPath = "E:\\qwq\\cos\\crawler";
//pixivcookie字符串
std::string _pixivCookie = {"first_visit_datetime_pc=2021-10-14+11%3A15%3A24; p_ab_id=2; p_ab_id_2=1; p_ab_d_id=1610904722; yuid_b=kZg3YnA; privacy_policy_notification=0; b_type=0; _fbp=fb.1.1642219417650.1928859381; adr_id=ld0rPPuejvJbg64XqbfIvho6NiVQRty4JZLeSZBkXVFPkYhl; login_ever=yes; __utmz=235335808.1649481273.36.7.utmcsr=google|utmccn=(organic)|utmcmd=organic|utmctr=(not%20provided); a_type=1; _td=2b529db0-ecc2-437c-a3a2-b79dcc7cfab9; privacy_policy_agreement=5; _ga_ZQEKG3EF2C=GS1.1.1663658686.1.0.1663658704.42.0.0; PHPSESSID=55653515_Wc4d3zHVdRN8LZPr5dV7jFj4znKppMn5; _ga_MZ1NL4PHH0=GS1.1.1672800499.2.1.1672800511.0.0.0; _im_vid=01GWM7FWT0YA6N33AWN0TJ5W5F; _gcl_au=1.1.1602369390.1680086275; _im_uid.3929=i.Jqdsrkl5TEeZpgpORwUNHw; __utmv=235335808.|2=login%20ever=yes=1^3=plan=normal=1^6=user_id=55653515=1^9=p_ab_id=2=1^10=p_ab_id_2=1=1^11=lang=zh=1; c_type=26; p_b_type=1; QSI_S_ZN_5hF4My7Ad6VNNAi=v:0:0; _gid=GA1.2.1720924258.1687571536; __utma=235335808.1257087362.1635155308.1687407289.1687689984.98;"};

extern const std::string _regex_pixiv_rule = "https://i.pximg.net/img-original[^\"]+";
extern const std::string _pixiv_ajax = "https://www.pixiv.net/ajax/illust/";

const int _socket_buffer_size = 1024 * 4;