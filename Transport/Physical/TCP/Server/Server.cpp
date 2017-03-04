#include "Server.h"

namespace Transport
{
	namespace TCP
	{
		Server::Server():
			m_Socket(SocketType::Stream)
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
			m_Socket.Send(data);
		}

		DataType::Bytes Server::Receive() const
		{
			return m_Socket.Receive();
		}

		// Test function begins
		void Server::Process()
		{
			static std::vector<Socket> sockets;
			Socket socket(SocketType::Stream);
			if (m_Socket.Accept(SocketAddress("127.0.0.1", 9999), socket))
			{
				sockets.push_back(socket);
			}

			for (auto socket : sockets)
			{
				std::string data("a quick brown fox jumps over the lazy dog");
				DataType::Bytes bytes(data.begin(), data.end());
				if (socket.Send(bytes))
				{
					continue;
				}
			}
		}
		// Test function ends

		bool Server::Open()
		{
			bool ret = true;

			ret &= m_Socket.SetNonBlocking();
			ret &= m_Socket.Bind(SocketAddress("127.0.0.1", 9999));
			ret &= m_Socket.Listen(0xFF);

			return ret;
		}

		void Server::Close()
		{

		}
	}
}