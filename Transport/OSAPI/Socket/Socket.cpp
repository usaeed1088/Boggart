#include "Socket.h"

#include "../OSAPI.h"

namespace Transport
{
	Socket::Socket(SocketType type):
		m_Type(type),
		m_Connected(false),
		m_SocketAPI(OSAPI::Instance())
	{
		Open(type);
	}

	Socket::~Socket()
	{
		Close();
	}

	bool Socket::Connected()
	{
		return m_Connected;
	}

	bool Socket::Open(SocketType type)
	{
		m_SocketId = m_SocketAPI->SocketOpen(SocketFamily::InterNetwork, type, 0);
		if (m_SocketId > 0)
		{
			return true;
		}

		return false;
	}

	bool Socket::Close()
	{
		return m_SocketAPI->SocketClose(m_SocketId);
	}

	// Server socket
	bool Socket::Bind(const SocketAddress& addr)
	{
		return m_SocketAPI->SocketBind(m_SocketId, addr);
	}

	bool Socket::Listen(int nClients)
	{
		return m_SocketAPI->SocketListen(m_SocketId, nClients);
	}

	bool Socket::Accept(const SocketAddress& addr, Socket& socket)
	{
		DataType::SocketId id = m_SocketAPI->SocketAccept(m_SocketId, addr);

		socket.m_SocketId = id;
		socket.m_Connected = true;
		
		return id > 0;
	}

	// Client socket
	bool Socket::Connect(const SocketAddress& server)
	{
		return m_SocketAPI->SocketConnect(m_SocketId, server);
	}

	// Common
	bool Socket::SetNonBlocking()
	{
		return m_SocketAPI->SocketIOControl(m_SocketId, SocketControl::NonBlocking, 1);
	}

	bool Socket::Send(const DataType::Bytes& data)
	{
		return m_SocketAPI->SocketSend(m_SocketId, data);
	}

	bool Socket::SendTo(const SocketAddress& destination, const DataType::Bytes& data)
	{
		return m_SocketAPI->SocketSendTo(m_SocketId, data, destination);
	}

	DataType::Bytes Socket::Receive()
	{
		return m_SocketAPI->SocketReceive(m_SocketId);
	}

	DataType::Bytes Socket::ReceiveFrom(const SocketAddress& source)
	{
		return m_SocketAPI->SocketReceiveFrom(m_SocketId, source);
	}
}