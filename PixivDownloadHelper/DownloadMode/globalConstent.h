#include <string>

#ifndef global_constent
#define global_constent
//��������������������������������·���������ļ�·����������������������������
//���ظ�Ŀ¼�����ļ�·��
extern const std::string _config_download_save_path;
//pixivcookie����ļ�·��
extern const std::string _config_pixivcookie_save_path;

//����������������������������������������������������������������������������

//�����������������������������û���Դ���á�����������������������������������
//���ظ�Ŀ¼,Ĭ��·��E:\\qwq\\cos\\crawler
extern std::string _downloadPath;
//pixivcookie�ַ���
extern std::string _pixivCookie;
//����������������������������������������������������������������������������

//��������������������������������ƥ����ʽ����������������������������������
extern const std::string _regex_pixiv_rule;									//pixivͼƬurlƥ�乫ʽ
extern const std::string _pixiv_ajax;									//pixiv ajax�ӿ�ǰ׺
//����������������������������������������������������������������������������

//���������������������������׽��ֻ�������С����������������������������������
extern const int _socket_buffer_size;
//����������������������������������������������������������������������������

//�����������������������������쳣���곣�����塪����������������������������
#define _M_WSASTART_ERR				"WSAStartup Error"			//winsock������ʼ���쳣
#define _M_DNS_ERR					"DNS Error"					//����ת���쳣
#define _M_SOCKET_CREATE_ERR		"Socket Create Error"		//����winsock�׽���ʧ��
#define _M_SOCKET_CONNECT_ERR		"Socket Connect Error"		//���ӵ�������ʧ��
#define _M_SOCKET_CLOSE_ERR			"Socket Close Error"		//�ر�winsock�׽���ʧ��

#define _M_SSL_CONTEXT_ERR			"SSL_CTX_new Error"			//ssl�����Ľ���ʧ��
#define _M_SSL_CREATE_ERR			"SSL New Error"				//ssl�׽��ִ���ʧ��
#define _M_SSL_CONNECT_ERR			"SSL Connect error"			//ssl����ʧ��
#define _M_SSL_WRITE_ERR			"SSL Write Error"			//ssl������Ϣʧ��

#define _DOWNLOAD_ERR				"Download Error"			//�����ļ�ʧ��
#define	_DOWNLOAD_SUCCESS			"Download Success"			//�����ļ��ɹ�
#define _REQUEST_ERR				"Request Error"				//����ҳ��ʧ��
#define _REQUEST_SUCCESS			"Request Success"			//����ҳ��ɹ�

#define _FILE_OPEN_ERR				"Error Open "				//�ļ���ʧ��
#define _FILE_CREATE_ERR			"Error Create "				//�ļ�����ʧ��

#define _EMPTY_STRING				""							//���ַ���
//����������������������������������������������������������������������������
#endif // !global_constent