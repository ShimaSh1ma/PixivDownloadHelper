#include "basicClass.h"
//int类型转为string类型，用于打印socket错误信息
static std::string intToString(const int& a) {
	std::stringstream ss;
	std::string re;
	ss << a;
	ss >> re;
	return re;
}

inline void MSocket::updateLog(const std::string& massage)
{
	this->log = {};
	log += massage;
}

std::string MSocket::returnLog()
{
	return this->log;
}


bool MSocket::socketInit(const std::string& Host,const std::string& _Port)
{
	//初始化socket环境
	_Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (_Result != 0) {
		updateLog(_M_WSASTART_ERR + intToString(WSAGetLastError()) + "\n");
		return false;
	}

	ZeroMemory(&ipAddr, sizeof(ipAddr));//置零避免错误
	ipAddr.ai_family = AF_UNSPEC;		//不指定ip协议簇
	ipAddr.ai_socktype = SOCK_STREAM;	//选择TCP
	ipAddr.ai_protocol = IPPROTO_TCP;	//选择TCP

	//———————————————通过getaddrinfo函数进行DNS请求————————————————
	_Result = getaddrinfo(Host.c_str(), _Port.c_str(), &ipAddr, &ipResult);
	if (_Result != 0) {
		updateLog(_M_DNS_ERR + intToString(WSAGetLastError()) + "\n");
		WSACleanup();
		return false;
	}
	//——————————————————————————————————————————————

	//———————————————————创建套接字——————————————————————
	mySocket = socket(ipResult->ai_family, ipResult->ai_socktype, ipResult->ai_protocol);
	//调用套接字函数为socket对象添加参数
	if (mySocket == INVALID_SOCKET) {			//套接字无效，清理套接字，返回失败标志
		updateLog(_M_SOCKET_CREATE_ERR + intToString(WSAGetLastError()) + "\n");
		freeaddrinfo(ipResult);
		WSACleanup();
		return false;
	}
	return true;
	//——————————————————————————————————————————————
}

bool MSocket::sslInit()
{
	//初始化
	SSL_library_init();
	SSL_load_error_strings();
	OpenSSL_add_all_algorithms();
	//建立SSL上下文
	ctx = SSL_CTX_new(meth);
	if (ctx == NULL) {
		updateLog(_M_SSL_CONTEXT_ERR);
		return false;
	}
	return true;
}

bool MSocket::sockConnect()
{
	//———————————————————连接到套接字—————————————————————
	_Result = connect(mySocket, ipResult->ai_addr, (int)ipResult->ai_addrlen);	//尝试连接服务器
	if (_Result == SOCKET_ERROR) {												//连接失败则关闭套接字
		updateLog(_M_SOCKET_CONNECT_ERR + intToString(WSAGetLastError()));
		closesocket(mySocket);
		mySocket = INVALID_SOCKET;
	}

	freeaddrinfo(ipResult);							//尝试连接后释放ip信息

	if (mySocket == INVALID_SOCKET) {				//连接失败后清理套接字服务
		WSACleanup();
		return false;
	}
	return true;
	//——————————————————————————————————————————————
}

bool MSocket::sslConnect(const std::string& _Host)
{
	//——————————————————建立SSL连接———————————————————————
	sslSocket = SSL_new(ctx);
	if (sslSocket == NULL) {
		updateLog(_M_SSL_CREATE_ERR);
		SSL_free(sslSocket);
		SSL_CTX_free(ctx);
		closesocket(mySocket);
		WSACleanup();
		return false;
	}

	SSL_set_mode(sslSocket, SSL_MODE_AUTO_RETRY);//自动重试
	SSL_set_tlsext_host_name(sslSocket, _Host.c_str());//tls握手失败时尝试指定主机名

	SSL_set_fd(sslSocket, mySocket);
	result = SSL_connect(sslSocket);
	if (result == -1) {
		updateLog(_M_SSL_CONNECT_ERR + SSL_get_error(sslSocket, result));
		SSL_free(sslSocket);
		SSL_CTX_free(ctx);
		closesocket(mySocket);
		WSACleanup();
		return false;
	}
	return true;
	//———————————————————————————————————————————————
}

bool MSocket::socketSend(const std::string& sendbuf)
{
	//——————————————————————向服务器发信息——————————————————
	result = SSL_write(sslSocket, sendbuf.c_str(), (int)sendbuf.length());
	if (result == -1) {

		updateLog(_M_SSL_WRITE_ERR + SSL_get_error(sslSocket, result));
		SSL_shutdown(sslSocket);
		SSL_free(sslSocket);
		SSL_CTX_free(ctx);
		closesocket(mySocket);
		WSACleanup();
		return false;
	}
	return true;
	//———————————————————————————————————————————————
}

std::string MSocket::socketReceiveHtml()
{
	//—————————————————从套接字缓冲中读取信息——————————————————
	int ret{};//接收socket返回值
	//开辟缓冲区
	char* recvbuf = new char[_socket_buffer_size];
	std::string temp;

	do {	//循环读取socket缓冲区
		result = SSL_read(sslSocket, recvbuf, _socket_buffer_size);
		if (result > 0) {
			for (int i = 0; i < result; i++) {
				temp += recvbuf[i];
			}
		}
		else if (result == 0) {
			updateLog(_REQUEST_SUCCESS);
		}
		else {
			updateLog(_REQUEST_ERR);
			delete[] recvbuf;
			return _EMPTY_STRING;
		}
	} while (result > 0 || SSL_get_error(sslSocket, ret) == SSL_ERROR_WANT_READ);
	//释放缓冲区
	delete[] recvbuf;

	//分割http响应报文，提取有效载荷部分
	size_t key = temp.find("\r\n\r\n", 0) + sizeof("\r\n\r\n") - 1;
	if (key == std::string::npos) {		//判断是否接收到http报文
		updateLog(_REQUEST_ERR);
		return _EMPTY_STRING;
	}
	//http响应解析
	HttpResponseParser responseParser;
	responseParser(temp.substr(0, key));
	//获取载荷，载荷为temp
	temp = temp.substr(key, temp.size() - key);

	//响应为200 OK则返回报文载荷
	if (responseParser.statusCode == "200") {
		return temp;
	}
	//响应不为200 则返回响应码
	if (responseParser.statusCode != "200") {
		return responseParser.statusCode;
	}
}

bool MSocket::socketReceiveFile(const std::string& file_dir)
{
	//————————从套接字缓冲中读取信息—————————————
	//开辟缓冲区
	std::array<char, _socket_buffer_size>* recvbuf = new std::array<char, _socket_buffer_size>;
	//暂时存放字节流的字符串
	std::string* temp = new std::string;

	int c{};
	//从套接字接收字节流———————————————————————
	do {
		result = SSL_read(sslSocket, recvbuf, _socket_buffer_size);
		if (result > 0) {
			for (int i = 0; i < result; i++) {
				*temp += (*recvbuf)[i];
			}
		}
		else if (result == 0) {
			updateLog(_DOWNLOAD_SUCCESS);
		}
		else {
			updateLog(_DOWNLOAD_ERR);
			qDebug() << "Socket close\r\n";
			delete temp;
			delete recvbuf;
			return false;
		}
	} while (result > 0 || SSL_get_error(sslSocket, result) == SSL_ERROR_WANT_READ);
	//接收完毕清除缓冲区
	delete recvbuf;

	//分割http响应报文，提取有效载荷部分———————————————————
	size_t key = temp->find("\r\n\r\n", 0) + sizeof("\r\n\r\n") - 1;
	if (key == std::string::npos) {		//判断是否接收到http报文
		updateLog(_DOWNLOAD_ERR);
		qDebug() << "No recieve\r\n";
		delete temp;
		return false;
	}
	//——————————判断文件是否完整—————————————
	//获取http报头
	HttpResponseParser responseParser;
	responseParser(temp->substr(0, key));
	//提取载荷
	*temp = temp->substr(key, temp->size() - key);
	//检查文件是否完整
	if ((size_t)strtoull(responseParser.findKeyOfHeader("Content-Length").c_str(), NULL, 0) != temp->size()) {
		qDebug() << "File incomplete\r\n" 
			<< (size_t)strtoull(responseParser.findKeyOfHeader("Content-Length").c_str(), NULL, 0) << "\r\n"
			<< temp->size() << "\r\n";
		delete temp;
		updateLog(_DOWNLOAD_ERR);
		return false;
	}
	//————————————————————————————————
	//将载荷写入文件—————————————————————————
	std::ofstream out(file_dir, std::ios::binary);
	if (out.is_open()) {
		out << *temp;
		out.close();
	}
	else {
		updateLog(_FILE_OPEN_ERR + file_dir);
	}
	delete temp;
	return true;
}

bool MSocket::socketClose()
{
	//——————————————————————关闭套接字———————————————————
	_Result = shutdown(mySocket, SD_SEND);			//尝试关闭套接字
	if (mySocket == SOCKET_ERROR) {					//关闭失败，清理套接字服务
		updateLog(_M_SOCKET_CLOSE_ERR);

		closesocket(mySocket);
		WSACleanup();
		return false;
	}
	closesocket(mySocket);
	WSACleanup();
	return true;
}

bool MSocket::sslClose()
{
	SSL_shutdown(sslSocket);
	SSL_free(sslSocket);
	SSL_CTX_free(ctx);
	return true;
}