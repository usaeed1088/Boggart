#include "Client.h"

#include <Lib/Instantiator.h>

namespace Boggart
{
	namespace Transport
	{
		namespace TCP
		{
			Client::Client(std::string myId, std::string serverIP, std::int32_t serverPort):
				TransportBase(std::string("TCPClient"), myId),
				m_ServerIP(serverIP),
				m_ServerPort(serverPort),
				m_Socket(PAL::Instantiator::ObjectFactory()->CreateSocket(PAL::Object::SocketType::Stream, PAL::Object::SocketFamily::Internetwork))
			{

			}

			Client::~Client()
			{
				
			}

			bool Client::OnOpen()
			{
				bool ret = true;

				ret &= m_Socket->Open();
				ret &= m_Socket->Connect(m_ServerIP, m_ServerPort);
				ret &= m_Socket->SetNonBlocking();

				return ret;
			}

			bool Client::OnClose()
			{
				return m_Socket->Close();
			}

			bool Client::OnSend(const std::vector<unsigned char>& data)
			{
				return m_Socket->Send(data);
			}

			std::vector<unsigned char> Client::OnReceive()
			{
				return m_Socket->Receive();
			}
		}
	}
}