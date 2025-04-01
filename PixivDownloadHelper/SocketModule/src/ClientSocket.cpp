#if defined(_WIN32)
#define NOMINMAX
#endif

#include "ClientSocket.h"

#include "HttpRequest.h"
#include "HttpResponseParser.h"
#include "MSocket.h"
#include "SocketConstant.h"
#include "UrlParser.h"

#include <array>
#include <cstring>
#include <limits>
#include <random>

#include <shared_mutex>

// 调用select函数传入的判断类型
enum class selectType {
    READ,
    WRITE,
    READ_AND_WRITE
};

// 读写socket池并发控制锁
static std::shared_mutex socketPoolMutex;

constexpr const size_t timeWaitSeconds = 5;

// socket池
std::unordered_map<socketIndex, std::unique_ptr<MSocket>> ClientSocket::socketPool{};

// 设置socket非阻塞
bool setSocketNonblocked(const SOCKET socket);
// 判断socket连接状态
bool waitForConnection(const SOCKET socket, int timeout_sec);
// 使用select检查套接字是否可用
bool selectSocket(const SOCKET socket, selectType type, int timeoutSecond = timeWaitSeconds);

void WSAInit() {
#if defined(_WIN32)
    WSADATA wsaData;
    // 初始化socket环境
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        exit(1);
        return;
    }
#endif
    sslInit();
}

void WSAClean() {
#if defined(_WIN32)
    WSACleanup();
#endif
}

void sslInit() {
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
}

socketIndex ClientSocket::creatSocket(const std::string& _host, const std::string& _port) {
    // 生成随机数做索引
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<socketIndex> distribution(0, std::numeric_limits<socketIndex>::max());

    socketIndex index;
    bool isIndexUnique = false;
    std::unique_lock<std::shared_mutex> uniquelock(socketPoolMutex);
    do {
        index = distribution(mt);
        isIndexUnique = socketPool.find(index) == socketPool.end();
    } while (!isIndexUnique);
    // 添加到统一管理池
    socketPool.insert({index, std::make_unique<MSocket>(_host.c_str(), _port.c_str())});
    return index;
}

MSocket* ClientSocket::findSocket(socketIndex& index) {
    std::shared_lock<std::shared_mutex> sharedlock(socketPoolMutex);
    auto it = socketPool.find(index);
    if (it == socketPool.end()) {
        index = -1;
        return nullptr;
    }
    return it->second.get();
}

void ClientSocket::deleteSocket(socketIndex& index) {
    std::unique_lock<std::shared_mutex> uniquelock(socketPoolMutex);
    socketPool.erase(index);
    index = -1;
}

socketIndex ClientSocket::reuseSocket(const std::string& _host) {
    std::shared_lock<std::shared_mutex> sharedlock(socketPoolMutex);
    for (const auto& pair : socketPool) {
        if (pair.second->getHost() != _host) {
            continue;
        }
        bool expected = false;
        if (pair.second->isBusy.compare_exchange_weak(expected, true)) {
            return pair.first;
        }
    }
    return -1;
}

socketIndex ClientSocket::connectToServer(const std::string& _host, const std::string& _port) {
    socketIndex index = ClientSocket::reuseSocket(_host);
    if (index != -1 && selectSocket(findSocket(index)->socket, selectType::WRITE)) {
        return index;
    } else {
        deleteSocket(index);
    }

    MSocket* _temp;
    do {
        index = creatSocket(_host, _port);
        _temp = findSocket(index);
    } while (_temp == nullptr);
    MSocket& _socket = *_temp;

    // 初始化socket信息结构体
    memset(&(_socket.ipAddr), 0, sizeof(_socket.ipAddr)); // 置零避免错误
    _socket.ipAddr.ai_family = AF_UNSPEC;                 // 不指定ip协议簇
    _socket.ipAddr.ai_socktype = SOCK_STREAM;             // 选择TCP
    _socket.ipAddr.ai_protocol = IPPROTO_TCP;             // 选择TCP

    // 建立SSL上下文
    _socket.ctx = SSL_CTX_new(_socket.meth);
    if (_socket.ctx == NULL) {
        _socket.errorLog = _M_SSL_CONTEXT_ERR;
        deleteSocket(index);
        return index;
    }

    // 通过getaddrinfo函数进行DNS请求
    _socket.result = getaddrinfo(_socket.host.c_str(), _socket.port.c_str(), &_socket.ipAddr, &_socket.ipResult);
    if (_socket.result != 0) {
        _socket.errorLog = _M_DNS_ERR + std::to_string(WSAGetLastError()) + "\n";
        freeaddrinfo(_socket.ipResult);
        deleteSocket(index);
        return index;
    }

    _socket.socket = socket(_socket.ipResult->ai_family, _socket.ipResult->ai_socktype, _socket.ipResult->ai_protocol);
    // 调用套接字函数为socket对象添加参数
    if (_socket.socket == INVALID_SOCKET || !setSocketNonblocked(_socket.socket)) {
        _socket.errorLog = _M_SOCKET_CREATE_ERR + std::to_string(WSAGetLastError()) + "\n";
        freeaddrinfo(_socket.ipResult);
        deleteSocket(index);
        return index;
    }

    // 连接到远程服务器
    _socket.result = connect(_socket.socket, _socket.ipResult->ai_addr, static_cast<int>(_socket.ipResult->ai_addrlen));
    bool errorOccurred;
#if defined(_WIN32)
    errorOccurred = _socket.result == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK;
#else
    errorOccurred = _socket.result == SOCKET_ERROR && errno == EINPROGRESS;
#endif
    if (errorOccurred) {
        _socket.errorLog = _M_SOCKET_CONNECT_ERR + std::to_string(WSAGetLastError());
        freeaddrinfo(_socket.ipResult);
        deleteSocket(index);
        return index;
    }

    freeaddrinfo(_socket.ipResult);

    if (!waitForConnection(_socket.socket, timeWaitSeconds)) {
        _socket.errorLog = _M_SOCKET_CONNECT_ERR + std::to_string(WSAGetLastError());
        deleteSocket(index);
        return index;
    }

    // 建立ssl连接
    _socket.sslSocket = SSL_new(_socket.ctx);
    if (_socket.sslSocket == NULL) {
        _socket.errorLog = _M_SSL_CREATE_ERR;
        deleteSocket(index);
        return index;
    }

    SSL_set_mode(_socket.sslSocket, SSL_MODE_AUTO_RETRY);              // 自动重试
    SSL_set_tlsext_host_name(_socket.sslSocket, _socket.host.c_str()); // tls握手失败时尝试指定主机名

    // 绑定套接字
    SSL_set_fd(_socket.sslSocket, static_cast<int>(_socket.socket));

    // 建立SSL连接
    while (true) {
        _socket.result = SSL_connect(_socket.sslSocket);
        if (_socket.result == 1) {
            // SSL连接成功
            return index;
        }

        // 获取错误码
        _socket.result = SSL_get_error(_socket.sslSocket, _socket.result);

        if (_socket.result == SSL_ERROR_WANT_READ || _socket.result == SSL_ERROR_WANT_WRITE) {
            if (_socket.result == SSL_ERROR_WANT_READ) {
                if (selectSocket(_socket.socket, selectType::READ)) {
                    continue;
                }
            } else if (_socket.result == SSL_ERROR_WANT_WRITE) {
                if (selectSocket(_socket.socket, selectType::WRITE)) {
                    continue;
                }
            }
            _socket.errorLog = _M_SSL_CONNECT_ERR;
            deleteSocket(index);
            return index;
        }
        _socket.errorLog =
            _M_SSL_CONNECT_ERR + std::to_string(_socket.result) + ": " + ERR_reason_error_string(ERR_get_error());
        deleteSocket(index);
        return index;
    }
}

bool ClientSocket::socketSend(socketIndex& index, const std::string& msg) {
    MSocket* _temp = findSocket(index);
    if (_temp == nullptr) {
        return false;
    }
    MSocket& _socket = *_temp;

    size_t sentLength = 0;
    while (sentLength < msg.length()) {
        _socket.result =
            SSL_write(_socket.sslSocket, msg.c_str() + sentLength, static_cast<int>(msg.length() - sentLength));
        if (_socket.result <= 0) {
            _socket.result = SSL_get_error(_socket.sslSocket, _socket.result);
            if (_socket.result == SSL_ERROR_WANT_WRITE) {
                if (selectSocket(_socket.socket, selectType::WRITE)) {
                    continue;
                }
            }
            _socket.errorLog = _M_SSL_WRITE_ERR + _socket.result;
            deleteSocket(index);
            return false;
        } else {
            sentLength += _socket.result;
        }
    }
    return true;
}

std::unique_ptr<HttpResponseParser> ClientSocket::socketReceive(socketIndex& index) {
    MSocket* _temp = findSocket(index);
    if (_temp == nullptr) {
        return nullptr;
    }
    MSocket& _socket = *_temp;

    std::string receivedData;
    std::array<char, _BUFFER_SIZE> recvBuffer;

    // 报文头与报文载荷分割点
    size_t dividePos = std::string::npos;

    while (dividePos == std::string::npos) {
        _socket.result = SSL_read(_socket.sslSocket, recvBuffer.data(), _BUFFER_SIZE);
        if (_socket.result <= 0) {
            _socket.result = SSL_get_error(_socket.sslSocket, _socket.result);
            if (_socket.result == SSL_ERROR_WANT_READ) {
                if (selectSocket(_socket.socket, selectType::READ)) {
                    continue;
                }
            }
            _socket.errorLog = _M_SSL_WRITE_ERR + _socket.result;
            deleteSocket(index);
            return nullptr;
        }
        receivedData.append(recvBuffer.data(), _socket.result);
        dividePos = receivedData.find("\r\n\r\n");
    }

    // 获取http响应报头
    std::string headData = receivedData.substr(0, dividePos);
    dividePos += 4;
    // 获取已经读取到的报文内容
    std::string bodyData = receivedData.substr(dividePos);

    std::unique_ptr<HttpResponseParser> parser(new HttpResponseParser);
    // 解析http响应头
    parser->parseResponse(headData);

    // 使用Transfer-Encoding: chunked判断接受
    bool chunked = (parser->getHttpHead("Transfer-Encoding") == "chunked");
    if (chunked) {
        parser->recvByChunckedData(bodyData);
        while (true) {
            _socket.result = SSL_read(_socket.sslSocket, recvBuffer.data(), _BUFFER_SIZE);
            if (_socket.result <= 0) {
                _socket.result = SSL_get_error(_socket.sslSocket, _socket.result);
                if (_socket.result == SSL_ERROR_WANT_READ) {
                    if (selectSocket(_socket.socket, selectType::READ)) {
                        continue;
                    }
                }
                _socket.errorLog = _M_SSL_WRITE_ERR + _socket.result;
                deleteSocket(index);
                return nullptr;
            }
            bodyData.append(recvBuffer.data(), _socket.result);
            if (parser->recvByChunckedData(bodyData) == 0) {
                break;
            }
        }
    }
    // 使用content-length判断接收
    else {
        size_t restLength = std::numeric_limits<socketIndex>::max();
        while (restLength > 0) {
            _socket.result =
                SSL_read(_socket.sslSocket, recvBuffer.data(), static_cast<int>(std::min(_BUFFER_SIZE, restLength)));
            if (_socket.result <= 0) {
                _socket.result = SSL_get_error(_socket.sslSocket, _socket.result);
                if (_socket.result == SSL_ERROR_WANT_READ) {
                    if (selectSocket(_socket.socket, selectType::READ)) {
                        continue;
                    }
                }
                _socket.errorLog = _M_SSL_WRITE_ERR + _socket.result;
                deleteSocket(index);
                return nullptr;
            }
            bodyData.append(recvBuffer.data(), _socket.result);
            restLength = parser->recvByContentLength(bodyData);
        }
    }
    return parser;
}

void ClientSocket::releaseSocket(socketIndex& index) {
    MSocket* _temp = findSocket(index);
    if (_temp == nullptr) {
        return;
    }
    MSocket& _socket = *_temp;
    _socket.isBusy.store(false);
}

void ClientSocket::disconnectToServer(socketIndex& index) {
    deleteSocket(index);
}

bool setSocketNonblocked(const SOCKET socket) {
#if defined(_WIN32)
    unsigned long mode = 1;
    if (ioctlsocket(socket, FIONBIO, &mode) != 0) {
        return false;
    }
#endif

#if defined(__LINUX__) || defined(__APPLE__)
    int flags = fcntl(socket, F_GETFL, 0);
    if (flags < 0) {
        return false;
    }
    flags |= O_NONBLOCK;
    if (fcntl(socket, F_SETFL, flags) < 0) {
        return false;
    }
#endif
    return true;
}

bool waitForConnection(const SOCKET socket, int timeout_sec) {
    fd_set writefds;
    FD_ZERO(&writefds);
    FD_SET(socket, &writefds);

    struct timeval timeout;
    memset(&timeout, 0, sizeof(timeval));
    timeout.tv_sec = timeout_sec;

    if (!selectSocket(socket, selectType::WRITE)) {
        return false;
    }

    int optval;
    socklen_t optlen = sizeof(optval);
    if (getsockopt(socket, SOL_SOCKET, SO_ERROR, (char*)&optval, &optlen) < 0) {
        return false;
    }

    if (optval != 0) {
        return false;
    }

    return true;
}

bool selectSocket(const SOCKET socket, selectType type, int timeoutSecond) {
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(socket, &fds);

    struct timeval timeout;
    memset(&timeout, 0, sizeof(timeval));
    timeout.tv_sec = timeoutSecond;

    int result = -1;
    if (type == selectType::READ) {
        result = select(static_cast<int>(socket + 1), &fds, NULL, NULL, &timeout);
    } else if (type == selectType::WRITE) {
        result = select(static_cast<int>(socket + 1), NULL, &fds, NULL, &timeout);
    } else if (type == selectType::READ_AND_WRITE) {
        result = select(static_cast<int>(socket + 1), &fds, &fds, NULL, &timeout);
    }

    if (result <= 0) {
        return false;
    }
    if (!FD_ISSET(socket, &fds)) {
        return false;
    }
    return true;
}
