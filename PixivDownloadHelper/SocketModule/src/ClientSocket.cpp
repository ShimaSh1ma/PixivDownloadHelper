#include "ClientSocket.h"

#include "UrlParser.h"
#include "HttpRequest.h"
#include "HttpResponseParser.h"
#include "SocketConstant.h"
#include "MSocket.h"

#include <random>

#ifdef _WIN32
WSADATA ClientSocket::wsaData = {};
#endif

void ClientSocket::WSAInit() {
#if defined(_WIN32)
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

size_t ClientSocket::creatSocket(const std::string& _host, const std::string& _port) {
    // 生成随机数做索引
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<size_t> distribution(0, std::numeric_limits<size_t>::max());

    size_t index;
    do {
        index = distribution(mt);
    } while (socketPool.find(index) != socketPool.end());
    // 添加到统一管理池
    socketPool.insert({ index, std::make_unique<MSocket>(_host.c_str(), _port.c_str()) });
    return index;
}

MSocket* ClientSocket::findSocket(size_t index) {
    auto it = socketPool.find(index);
    if (it == socketPool.end()) {
        return nullptr;
    }
    return it->second.get();
}

void ClientSocket::deleteSocket(size_t index) {
    socketPool.erase(index);
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

    // 对于非阻塞connect, select可以用来等待连接完成
    int result = select(_socket.socket + 1, NULL, &writefds, NULL, &timeout);
    if (result <= 0) {
        return false;
    }

    // 检查socket是否在write set中
    if (!FD_ISSET(_socket.socket, &writefds)) {
        return false;
    }

    int optval;
    socklen_t optlen = sizeof(optval);
    if (getsockopt(_socket.socket, SOL_SOCKET, SO_ERROR, (char*)&optval, &optlen) < 0) {
        return false;
    }

    if (optval != 0) {
        // 无法连接
        return false;
    }

    return true;
}

std::unordered_map<size_t, std::unique_ptr<MSocket>> ClientSocket::socketPool{};

void ClientSocket::sslInit() {
    //初始化
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
}

size_t ClientSocket::connectToServer(const std::string& _host, const std::string& _port) {
    size_t index = creatSocket(_host, _port);

    MSocket* _temp = findSocket(index);
    if (_temp == nullptr) { return -1; }
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
        return -1;
    }

    //通过getaddrinfo函数进行DNS请求
    _socket.result = getaddrinfo(_socket.host.c_str(), _socket.port.c_str(), &_socket.ipAddr, &_socket.ipResult);
    if (_socket.result != 0) {
        _socket.errorLog = _M_DNS_ERR + std::to_string(WSAGetLastError()) + "\n";
        freeaddrinfo(_socket.ipResult);
        deleteSocket(index);
        return -1;
    }

    _socket.socket = socket(_socket.ipResult->ai_family, _socket.ipResult->ai_socktype, _socket.ipResult->ai_protocol);
    //调用套接字函数为socket对象添加参数
    if (_socket.socket == INVALID_SOCKET || !setSocketNonblocked(_socket)) {
        _socket.errorLog = _M_SOCKET_CREATE_ERR + std::to_string(WSAGetLastError()) + "\n";
        freeaddrinfo(_socket.ipResult);
        deleteSocket(index);
        return -1;
    }

    //连接到远程服务器
    _socket.result = connect(_socket.socket, _socket.ipResult->ai_addr, static_cast<int>(_socket.ipResult->ai_addrlen));
    if (_socket.result == SOCKET_ERROR || !waitForConnection(_socket, 5)) {
        _socket.errorLog = _M_SOCKET_CONNECT_ERR + std::to_string(WSAGetLastError());
        freeaddrinfo(_socket.ipResult);
        deleteSocket(index);
        return -1;
    }

    freeaddrinfo(_socket.ipResult);

    //建立ssl连接
    _socket.sslSocket = SSL_new(_socket.ctx);
    if (_socket.sslSocket == NULL) {
        _socket.errorLog = _M_SSL_CREATE_ERR;
        deleteSocket(index);
        return -1;
    }

    SSL_set_mode(_socket.sslSocket, SSL_MODE_AUTO_RETRY);//自动重试
    SSL_set_tlsext_host_name(_socket.sslSocket, _socket.host.c_str());//tls握手失败时尝试指定主机名

    //建立SSL连接
    SSL_set_fd(_socket.sslSocket, _socket.socket);
    _socket.result = SSL_connect(_socket.sslSocket);
    if (_socket.result == -1) {
        _socket.errorLog = _M_SSL_CONNECT_ERR + SSL_get_error(_socket.sslSocket, _socket.result);
        deleteSocket(index);
        return -1;
    }
    return index;
}

void ClientSocket::socketSend(size_t index, const std::string& sendBuf)
{
    MSocket* _temp = findSocket(index);
    if (_temp == nullptr) { return; }
    MSocket& _socket = *_temp;

    //发送报文
    _socket.result = SSL_write(_socket.sslSocket, sendBuf.c_str(), static_cast<int>(sendBuf.length()));
    if (_socket.result == -1) {
        _socket.errorLog = _M_SSL_WRITE_ERR + SSL_get_error(_socket.sslSocket, _socket.result);
        _socket.socketClose();
    }
}

std::string ClientSocket::socketReceive(size_t index)
{
    MSocket* _temp = findSocket(index);
    if (_temp == nullptr) { return ""; }
    MSocket& _socket = *_temp;

    //接收socket返回值
    int ret{};
    //开辟缓冲区
    std::unique_ptr<char[]> recvbuf(new char[_BUFFER_SIZE]);
    std::string temp;
    //循环读取socket缓冲区
    do {
        _socket.result = SSL_read(_socket.sslSocket, recvbuf.get(), _BUFFER_SIZE);
        if (_socket.result > 0) {
            for (int i = 0; i < _socket.result; i++) {
                temp += recvbuf[i];
            }
        }
        else if (_socket.result == 0) {
            _socket.errorLog = _REQUEST_SUCCESS;
        }
        else {
            _socket.errorLog = _REQUEST_ERR;
            return "";
        }
    } while (_socket.result > 0 || SSL_get_error(_socket.sslSocket, ret) == SSL_ERROR_WANT_READ);

    //分割http响应报文，提取有效载荷部分
    size_t key = temp.find("\r\n\r\n", 0) + sizeof("\r\n\r\n") - 1;
    //判断是否接收到http报文
    if (key == std::string::npos) {
        _socket.errorLog = _REQUEST_ERR;
        return "";
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
    return "";
}

void ClientSocket::disconnectToServer(size_t index) {
    deleteSocket(index);
}
