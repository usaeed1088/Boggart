#pragma once

#include "Structs.h"
#include "../SocketAPI.h"

namespace Transport
{
	class Socket
	{
	private:
		SocketType m_Type;
		bool m_Connected;
		DataType::SocketId m_SocketId;

	private:
		SocketAPI* m_SocketAPI;

	public:
		Socket(SocketType type);
		virtual ~Socket();

		bool Connected();

	private:
		bool Open(SocketType type);
		bool Close();

	public:
		// Server socket
		bool Bind(const SocketAddress& addr);
		bool Listen(int nClients);
		bool Accept(const SocketAddress& addr, Socket& socket);

		// Client socket
		bool Connect(const SocketAddress& server);

		// Common
		bool SetNonBlocking();

		bool Send(const DataType::Bytes& data);
		bool SendTo(const SocketAddress& destination, const DataType::Bytes& data);

		DataType::Bytes Receive();
		DataType::Bytes ReceiveFrom(const SocketAddress& source);
	};
}