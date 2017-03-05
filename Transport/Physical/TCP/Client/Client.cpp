#include "Client.h"

namespace Transport
{
	namespace TCP
	{
		Client::Client(SocketAddress serverAddress):
			m_Socket(SocketType::Stream),
			m_ServerAddress(serverAddress)
		{
			if (Open())
			{
				m_Connected = true;
			}
		}

		Client::~Client()
		{
			Close();
		}

		void Client::Send(const DataType::Bytes& data) const
		{
			m_Socket.Send(data);
		}

		DataType::Bytes Client::Receive() const
		{
			return m_Socket.Receive();
		}

		bool Client::Open()
		{
			bool ret = true;
			ret &= m_Socket.Connect(m_ServerAddress);
			ret &= m_Socket.SetNonBlocking();
			return ret;
		}

		void Client::Close()
		{
			m_Socket.Close();
		}
	}
}