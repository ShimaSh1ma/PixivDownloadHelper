#include "MSocket.h"

//MSocket
MSocket::MSocket(const char* host, const char* port) {
	setHostAndPort(host, port);
}

MSocket::~MSocket() {
	this->socketClose();
}

void MSocket::setHostAndPort(const char* host, const char* port) noexcept {
	this->host = host;
	this->port = port;
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
