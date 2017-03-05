#include "Server.h"

namespace Transport
{
	namespace TCP
	{
		Server::Server(SocketAddress myAddress):
			m_Socket(SocketType::Stream),
			m_MyAddress(myAddress)
		{
			if (Open())
			{
				m_Connected = true;
			}
		}

		Server::~Server()
		{
			Close();
		}

		void Server::Send(const DataType::Bytes& data) const
		{
			for (auto client : m_Clients)
			{
				client.Send(data);
			}
		}

		DataType::Bytes Server::Receive() const
		{
			return m_Socket.Receive();
		}

		// Test function begins
		void Server::Process()
		{
			Socket socket(SocketType::Stream);
			if (m_Socket.Accept(m_MyAddress, socket))
			{
				m_Clients.push_back(socket);
			}
		}
		// Test function ends

		bool Server::Open()
		{
			bool ret = true;

			ret &= m_Socket.SetNonBlocking();
			ret &= m_Socket.Bind(m_MyAddress);
			ret &= m_Socket.Listen(0xFF);

			return ret;
		}

		void Server::Close()
		{
			m_Socket.Close();
		}
	}
}