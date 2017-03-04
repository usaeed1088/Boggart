#pragma once

#include "Socket/Structs.h"

namespace Transport
{
	class SocketAPI
	{
	protected:
		SocketAPI() {}
		virtual ~SocketAPI() {}

	public:
		virtual DataType::SocketId SocketOpen(SocketFamily family, SocketType type, int protocol) = 0;
		virtual bool SocketClose(int socket) = 0;
		virtual bool SocketBind(int socket, const SocketAddress& addr) = 0;
		virtual bool SocketListen(int socket, int nClients) = 0;
		virtual DataType::SocketId SocketAccept(int socket, const SocketAddress& addr) = 0;
		virtual bool SocketConnect(int socket, const SocketAddress& sock_in) = 0;
		virtual bool SocketIOControl(int socket, SocketControl control, unsigned long arg) = 0;
		virtual bool SocketSend(int socket, const DataType::Bytes& data) = 0;
		virtual bool SocketSendTo(int socket, const DataType::Bytes& data, const SocketAddress& sendToAddress) = 0;
		virtual DataType::Bytes SocketReceive(int socket) = 0;
		virtual DataType::Bytes SocketReceiveFrom(int socket, const SocketAddress& recvFrom) = 0;
	};
}