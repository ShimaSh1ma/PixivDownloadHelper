#include "MSocket.h"

void ClientSocket::WSAInit() {
	//初始化socket环境
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		exit(1);
		return;
	}
	atexit(WSAClean);
}

void ClientSocket::WSAClean() {
	WSACleanup();
	return;
}

void ClientSocket::sslInit() {
	//初始化
	SSL_library_init();
	SSL_load_error_strings();
	OpenSSL_add_all_algorithms();
}

void ClientSocket::sslConnectToServer(MSocket& _socket) {
	//初始化socket信息结构体
	ZeroMemory(&(_socket.ipAddr), sizeof(_socket.ipAddr));//置零避免错误
	_socket.ipAddr.ai_family = AF_UNSPEC;		//不指定ip协议簇
	_socket.ipAddr.ai_socktype = SOCK_STREAM;	//选择TCP
	_socket.ipAddr.ai_protocol = IPPROTO_TCP;	//选择TCP

	//建立SSL上下文
	_socket.ctx = SSL_CTX_new(_socket.meth);
	if (_socket.ctx == NULL) {
		_socket.errorLog = _M_SSL_CONTEXT_ERR;
		_socket.socket = INVALID_SOCKET;
		return;
	}

	//通过getaddrinfo函数进行DNS请求
	_socket.result = getaddrinfo(_socket.host.c_str(), _socket.port.c_str(), &_socket.ipAddr, &_socket.ipResult);
	if (_socket.result != 0) {
		_socket.errorLog = _M_DNS_ERR + std::to_string(WSAGetLastError()) + "\n";
		_socket.socket = INVALID_SOCKET;
		freeaddrinfo(_socket.ipResult);
		return;
	}

	_socket.socket = socket(_socket.ipResult->ai_family, _socket.ipResult->ai_socktype, _socket.ipResult->ai_protocol);
	//调用套接字函数为socket对象添加参数
	if (_socket.socket == INVALID_SOCKET) {			//套接字无效，清理套接字，返回失败标志
		_socket.errorLog = _M_SOCKET_CREATE_ERR + std::to_string(WSAGetLastError()) + "\n";
		_socket.socket = INVALID_SOCKET;
		freeaddrinfo(_socket.ipResult);
		return;
	}

	//连接到远程服务器
	_socket.result = connect(_socket.socket, _socket.ipResult->ai_addr, static_cast<int>(_socket.ipResult->ai_addrlen));
	if (_socket.result == SOCKET_ERROR) {
		closesocket(_socket.socket);
		_socket.errorLog = _M_SOCKET_CONNECT_ERR + std::to_string(WSAGetLastError());
		_socket.socket = INVALID_SOCKET;
	}

	freeaddrinfo(_socket.ipResult);

	//建立ssl连接
	_socket.sslSocket = SSL_new(_socket.ctx);
	if (_socket.sslSocket == NULL) {
		SSL_free(_socket.sslSocket);
		SSL_CTX_free(_socket.ctx);
		closesocket(_socket.socket);
		_socket.errorLog = _M_SSL_CREATE_ERR;
		_socket.socket = INVALID_SOCKET;
		return;
	}

	SSL_set_mode(_socket.sslSocket, SSL_MODE_AUTO_RETRY);//自动重试
	SSL_set_tlsext_host_name(_socket.sslSocket, _socket.host.c_str());//tls握手失败时尝试指定主机名

	//建立SSL连接
	SSL_set_fd(_socket.sslSocket, _socket.socket);
	_socket.result = SSL_connect(_socket.sslSocket);
	if (_socket.result == -1) {
		SSL_free(_socket.sslSocket);
		SSL_CTX_free(_socket.ctx);
		closesocket(_socket.socket);
		_socket.errorLog = _M_SSL_CONNECT_ERR + SSL_get_error(_socket.sslSocket, _socket.result);
		_socket.socket = INVALID_SOCKET;
		return;
	}

	return;
}

void ClientSocket::socketSend(MSocket& _socket, const std::string& sendBuf)
{
	//发送报文
	_socket.result = SSL_write(_socket.sslSocket, sendBuf.c_str(), static_cast<int>(sendBuf.length()));
	if (_socket.result == -1) {
		_socket.errorLog = _M_SSL_WRITE_ERR + SSL_get_error(_socket.sslSocket, _socket.result);
		SSL_shutdown(_socket.sslSocket);
		SSL_free(_socket.sslSocket);
		SSL_CTX_free(_socket.ctx);
		closesocket(_socket.socket);
		return;
	}

	return;
}

std::string ClientSocket::socketReceive()
{
	//接收socket返回值
	int ret{};
	//开辟缓冲区
	char* recvbuf = new char[_socket_buffer_size];
	std::string temp;
	//循环读取socket缓冲区
	do {
		result = SSL_read(sslSocket, recvbuf, _socket_buffer_size);
		if (result > 0) {
			for (int i = 0; i < result; i++) {
				temp += recvbuf[i];
			}
		}
		else if (result == 0) {
			errorLog = _REQUEST_SUCCESS;
		}
		else {
			errorLog = _REQUEST_ERR;
			delete[] recvbuf;
			return _EMPTY_STRING;
		}
	} while (result > 0 || SSL_get_error(sslSocket, ret) == SSL_ERROR_WANT_READ);
	//释放缓冲区
	delete[] recvbuf;

	//分割http响应报文，提取有效载荷部分
	size_t key = temp.find("\r\n\r\n", 0) + sizeof("\r\n\r\n") - 1;
	//判断是否接收到http报文
	if (key == std::string::npos) {
		errorLog = _REQUEST_ERR;
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
	return _EMPTY_STRING;
}

void ClientSocket::sslDisconnectToServer(MSocket& _socket) {
	//断开ssl连接
	SSL_shutdown(_socket.sslSocket);
	SSL_free(_socket.sslSocket);
	SSL_CTX_free(_socket.ctx);

	//断开tcp连接
	_socket.result = shutdown(_socket.socket, SD_SEND);
	if (_socket.socket == SOCKET_ERROR) {
		_socket.errorLog = _M_SOCKET_CLOSE_ERR;
		closesocket(_socket.socket);
		_socket.socket = INVALID_SOCKET;
	}
}

//MSocket
MSocket::MSocket(const char* host, const char* port) {
	setHostAndPort(host, port);
}

void MSocket::setHostAndPort(const char* host, const char* port) {
	this->host = host;
	this->port = port;
}
