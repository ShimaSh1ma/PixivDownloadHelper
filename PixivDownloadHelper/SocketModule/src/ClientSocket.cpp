#if defined(_WIN32)
#define NOMINMAX
#endif

#include "ClientSocket.h"

#include "UrlParser.h"
#include "HttpRequest.h"
#include "HttpResponseParser.h"
#include "SocketConstant.h"
#include "MSocket.h"

#include <array>
#include <cstring>
#include <random>
#include <limits>

void ClientSocket::WSAInit() {
#if defined(_WIN32)
	WSADATA wsaData;
	//初始化socket环境
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		exit(1);
		return;
	}
#endif
}

void ClientSocket::WSAClean() {
#if defined(_WIN32)
	WSACleanup();
#endif
}

socketIndex ClientSocket::creatSocket(const std::string& _host, const std::string& _port) {
	// 生成随机数做索引
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<socketIndex> distribution(0, std::numeric_limits<socketIndex>::max());

	socketIndex index;
	do {
		index = distribution(mt);
	} while (socketPool.find(index) != socketPool.end());
	// 添加到统一管理池
	socketPool.insert({ index, std::make_unique<MSocket>(_host.c_str(), _port.c_str()) });
	return index;
}

MSocket* ClientSocket::findSocket(socketIndex index) {
	auto it = socketPool.find(index);
	if (it == socketPool.end()) {
		return nullptr;
	}
	return it->second.get();
}

void ClientSocket::deleteSocket(socketIndex& index) {
	socketPool.erase(index);
	index = -1;
}

bool ClientSocket::setSocketNonblocked(MSocket& _socket) {
#if  defined(_WIN32)
	unsigned long mode = 1;
	if (ioctlsocket(_socket.socket, FIONBIO, &mode) != 0) {
		return false;
	}
#endif

#if defined(__LINUX__)||defined(__APPLE__)
	int flags = fcntl(_socket.socket, F_GETFL, 0);
	if (flags < 0) {
		return false;
	}
	flags |= O_NONBLOCK;
	if (fcntl(_socket.socket, F_SETFL, flags) < 0) {
		return false;
	}
#endif
	return true;
}

bool ClientSocket::waitForConnection(MSocket& _socket, int timeout_sec) {
	fd_set writefds;
	FD_ZERO(&writefds);
	FD_SET(_socket.socket, &writefds);

	struct timeval timeout;
	timeout.tv_sec = timeout_sec;
	timeout.tv_usec = 0;

	int result = select(_socket.socket + 1, NULL, &writefds, NULL, &timeout);
	if (result <= 0) {
		return false;
	}

	if (!FD_ISSET(_socket.socket, &writefds)) {
		return false;
	}

	int optval;
	socklen_t optlen = sizeof(optval);
	if (getsockopt(_socket.socket, SOL_SOCKET, SO_ERROR, (char*)&optval, &optlen) < 0) {
		return false;
	}

	if (optval != 0) {
		return false;
	}

	return true;
}

std::unordered_map<socketIndex, std::unique_ptr<MSocket>> ClientSocket::socketPool{};

void ClientSocket::sslInit() {
	//初始化
	SSL_library_init();
	SSL_load_error_strings();
	OpenSSL_add_all_algorithms();
}

socketIndex ClientSocket::connectToServer(const std::string& _host, const std::string& _port) {
	socketIndex index = creatSocket(_host, _port);

	MSocket* _temp = findSocket(index);
	if (_temp == nullptr) {
		index = -1;
		return index;
	}
	MSocket& _socket = *_temp;

	//初始化socket信息结构体
	memset(&(_socket.ipAddr), 0, sizeof(_socket.ipAddr));//置零避免错误
	_socket.ipAddr.ai_family = AF_UNSPEC;		//不指定ip协议簇
	_socket.ipAddr.ai_socktype = SOCK_STREAM;	//选择TCP
	_socket.ipAddr.ai_protocol = IPPROTO_TCP;	//选择TCP

	//建立SSL上下文
	_socket.ctx = SSL_CTX_new(_socket.meth);
	if (_socket.ctx == NULL) {
		_socket.errorLog = _M_SSL_CONTEXT_ERR;
		deleteSocket(index);
		return index;
	}

	//通过getaddrinfo函数进行DNS请求
	_socket.result = getaddrinfo(_socket.host.c_str(), _socket.port.c_str(), &_socket.ipAddr, &_socket.ipResult);
	if (_socket.result != 0) {
		_socket.errorLog = _M_DNS_ERR + std::to_string(WSAGetLastError()) + "\n";
		freeaddrinfo(_socket.ipResult);
		deleteSocket(index);
		return index;
	}

	_socket.socket = socket(_socket.ipResult->ai_family, _socket.ipResult->ai_socktype, _socket.ipResult->ai_protocol);
	//调用套接字函数为socket对象添加参数
	if (_socket.socket == INVALID_SOCKET || !setSocketNonblocked(_socket)) {
		_socket.errorLog = _M_SOCKET_CREATE_ERR + std::to_string(WSAGetLastError()) + "\n";
		freeaddrinfo(_socket.ipResult);
		deleteSocket(index);
		return index;
	}

	//连接到远程服务器
	_socket.result = connect(_socket.socket, _socket.ipResult->ai_addr, static_cast<int>(_socket.ipResult->ai_addrlen));
	std::string a = std::to_string(WSAGetLastError());
	if (!waitForConnection(_socket, 5) || _socket.result == SOCKET_ERROR) {
		_socket.errorLog = _M_SOCKET_CONNECT_ERR + std::to_string(WSAGetLastError());
		freeaddrinfo(_socket.ipResult);
		deleteSocket(index);
		return index;
	}

	freeaddrinfo(_socket.ipResult);

	//建立ssl连接
	_socket.sslSocket = SSL_new(_socket.ctx);
	if (_socket.sslSocket == NULL) {
		_socket.errorLog = _M_SSL_CREATE_ERR;
		deleteSocket(index);
		return index;
	}

	SSL_set_mode(_socket.sslSocket, SSL_MODE_AUTO_RETRY);//自动重试
	SSL_set_tlsext_host_name(_socket.sslSocket, _socket.host.c_str());//tls握手失败时尝试指定主机名

	//建立SSL连接
	SSL_set_fd(_socket.sslSocket, _socket.socket);
	_socket.result = SSL_connect(_socket.sslSocket);
	if (_socket.result == -1) {
		_socket.errorLog = _M_SSL_CONNECT_ERR + SSL_get_error(_socket.sslSocket, _socket.result);
		deleteSocket(index);
		return index;
	}
	return index;
}

bool ClientSocket::socketSend(socketIndex& index, const std::string& msg)
{
	MSocket* _temp = findSocket(index);
	if (_temp == nullptr) {
		index = -1;
		return false;
	}
	MSocket& _socket = *_temp;

	size_t sentLength = 0;

	while (sentLength < msg.length()) {
		_socket.result = SSL_write(_socket.sslSocket, msg.c_str() + sentLength, static_cast<int>(msg.length() - sentLength));
		if (_socket.result <= 0) {
			_socket.result = SSL_get_error(_socket.sslSocket, _socket.result);
			if (_socket.result == SSL_ERROR_WANT_WRITE) {
				fd_set set;
				FD_ZERO(&set);
				FD_SET(_socket.socket, &set);

				int selectErr = select(_socket.socket + 1, NULL, &set, NULL, nullptr);
				if (selectErr > 0) {
					continue;
				}
				else {
					break;
				}
			}
			else {
				_socket.errorLog = _M_SSL_WRITE_ERR + _socket.result;
				deleteSocket(index);
				return false;
			}
		}
		else {
			sentLength += _socket.result;
		}
	}
	return true;
}

std::string ClientSocket::socketReceive(socketIndex& index)
{
	MSocket* _temp = findSocket(index);
	if (_temp == nullptr) {
		index = -1;
		return "";
	}
	MSocket& _socket = *_temp;

	std::string receivedData;
	size_t receivedLength = 0;
	std::array<char, _BUFFER_SIZE> recvBuffer;

	size_t dividePos = std::string::npos;
	while (dividePos == std::string::npos) {
		_socket.result = SSL_read(_socket.sslSocket, recvBuffer.data(), _BUFFER_SIZE);
		if (_socket.result <= 0) {
			_socket.result = SSL_get_error(_socket.sslSocket, _socket.result);
			if (_socket.result == SSL_ERROR_WANT_READ) {
				continue;
			}
			_socket.errorLog = _M_SSL_WRITE_ERR + _socket.result;
			deleteSocket(index);
			return "";
		}
		receivedData.append(recvBuffer.data(), _socket.result);
		dividePos = receivedData.find("\r\n\r\n");
	}

	dividePos += 4;
	std::string headData = receivedData.substr(0, dividePos);
	std::unique_ptr<HttpResponseParser> parser(new HttpResponseParser);
	(*parser)(headData);
	size_t contentLength = std::stoull(parser->getHttpHead("Content-Length"));

	receivedLength = receivedData.length() - headData.length();
	while (receivedLength < contentLength) {
		_socket.result = SSL_read(_socket.sslSocket, recvBuffer.data(), std::min(_BUFFER_SIZE, contentLength - receivedLength));
		if (_socket.result <= 0) {
			_socket.result = SSL_get_error(_socket.sslSocket, _socket.result);
			if (_socket.result == SSL_ERROR_WANT_READ) {
				continue;
			}
			_socket.errorLog = _M_SSL_WRITE_ERR + _socket.result;
			deleteSocket(index);
			return "";
		}
		receivedData.append(recvBuffer.data(), _socket.result);
		receivedData += _socket.result;
	}

	return receivedData.substr(dividePos);
}

void ClientSocket::disconnectToServer(socketIndex& index) {
	deleteSocket(index);
}
