#include <string>

#ifndef global_constent
#define global_constent
//——————————————下载路径和设置文件路径—————————————
//下载根目录设置文件路径
extern const std::string _config_download_save_path;
//pixivcookie存放文件路径
extern const std::string _config_pixivcookie_save_path;

//——————————————————————————————————————

//——————————————用户资源设置——————————————————
//下载根目录,默认路径E:\\qwq\\cos\\crawler
extern std::string _downloadPath;
//pixivcookie字符串
extern std::string _pixivCookie;
//——————————————————————————————————————

//——————————————正则匹配表达式—————————————————
extern const std::string _regex_pixiv_rule;									//pixiv图片url匹配公式
extern const std::string _pixiv_ajax;									//pixiv ajax接口前缀
//——————————————————————————————————————

//—————————————套接字缓冲区大小—————————————————
extern const int _socket_buffer_size;
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
#endif // !global_constent