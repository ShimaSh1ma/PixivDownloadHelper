#include "MSocket.h"

// MSocket
MSocket::MSocket(const char* _host, const char* _port) {
    setHostAndPort(_host, _port);
}

MSocket::~MSocket() {
    socketClose();
}

void MSocket::setHostAndPort(const char* _host, const char* _port) noexcept {
    host = _host;
    port = _port;
}

const std::string MSocket::getHost() {
    return this->host;
}

void MSocket::socketClose() {
    if (sslSocket) {
        SSL_shutdown(sslSocket);
        SSL_free(sslSocket);
        sslSocket = nullptr;
    }

    if (ctx) {
        SSL_CTX_free(ctx);
        ctx = nullptr;
    }

    if (socket != INVALID_SOCKET) {
        closesocket(socket);
        socket = INVALID_SOCKET;
    }
}
