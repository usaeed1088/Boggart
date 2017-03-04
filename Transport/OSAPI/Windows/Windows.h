#pragma once

#include "../OSAPI.h"

namespace Transport
{
	class Windows : public OSAPI
	{
	private:
		friend class OSAPI;
		Windows();
		~Windows() override;

	public:
		// Socket API
		DataType::SocketId SocketOpen(SocketFamily family, SocketType type, int protocol) override;
		bool SocketClose(int socket) override;
		bool SocketBind(int socket, const SocketAddress& addr) override;
		bool SocketListen(int socket, int nClients) override;
		DataType::SocketId SocketAccept(int socket, const SocketAddress& addr) override;
		bool SocketConnect(int socket, const SocketAddress& sock_in) override;
		bool SocketIOControl(int socket, SocketControl control, unsigned long arg) override;
		bool SocketSend(int socket, const DataType::Bytes& data) override;
		bool SocketSendTo(int socket, const DataType::Bytes& data, const SocketAddress& sendToAddress) override;
		DataType::Bytes SocketReceive(int socket) override;
		DataType::Bytes SocketReceiveFrom(int socket, const SocketAddress& recvFrom) override;
	};
}