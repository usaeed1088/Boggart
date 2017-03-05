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
			return DataType::Bytes();
			//return m_Socket.Receive();
		}

		void Server::Process() const
		{
			ProcessConnections();
			ProcessIncomingData();
		}

		void Server::ProcessConnections() const
		{
			Socket socket(SocketType::Stream);
			if (m_Socket.Accept(m_MyAddress, socket))
			{
				m_Clients.push_back(socket);
			}
		}

		void Server::ProcessIncomingData() const
		{
			// Receive the incoming data from each client
			for (DataType::Size i = 0; i < m_Clients.size(); i++)
			{
				DataType::Bytes data = m_Clients[i].Receive();
				if (data.empty())
				{
					continue;
				}

				// Forward to other clients
				for (DataType::Size j = 0; j < m_Clients.size(); j++)
				{
					if (j == i)
					{
						continue;
					}

					m_Clients[j].Send(data);
				}
			}
		}

		bool Server::Open()
		{
			bool ret = true;

			ret &= m_Socket.Open();
			ret &= m_Socket.SetNonBlocking();
			ret &= m_Socket.Bind(m_MyAddress);
			ret &= m_Socket.Listen(0xFF);

			return ret;
		}

		void Server::Close()
		{
			for (Socket& client : m_Clients)
			{
				client.Close();
			}

			m_Socket.Close();
		}
	}
}