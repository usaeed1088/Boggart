#include "Client.h"

#include "../Definition/Definition.h"

#include <Lib/Instantiator.h>
#include <Message/Types/Generic/Generic.h>

namespace Boggart
{
	namespace Transport
	{
		namespace UDP
		{
			Client::Client(std::string myId, std::string serverIP, std::int32_t serverPort) :
				TransportBase(std::string("UDPClient"), myId),
				m_ServerIP(serverIP),
				m_ServerPort(serverPort),
				m_Socket(PAL::Instantiator::ObjectFactory()->CreateSocket(PAL::Object::SocketType::Datagram, PAL::Object::SocketFamily::Internetwork))
			{

			}

			Client::~Client()
			{
				Close();
			}

			bool Client::OnOpen()
			{
				bool ret = true;

				ret &= m_Socket->Open();
				ret &= m_Socket->Bind(0); // Let the OS assign us a port
				ret &= m_Socket->SetNonBlocking();

				// This is required to introduce
				// this client to UDP server
				PokeServer();

				return ret;
			}

			bool Client::OnClose()
			{
				return m_Socket->Close();
			}

			bool Client::OnSend(const std::vector<unsigned char>& data)
			{
				return m_Socket->SendTo(m_ServerIP, m_ServerPort, data);
			}

			std::vector<unsigned char> Client::OnReceive()
			{
				std::string source;
				std::int32_t port;
				return m_Socket->ReceiveFrom(source, port);
			}

			void Client::PokeServer()
			{
				Message::Type::Generic poke(Definition::PokeMessage, std::vector<unsigned char>());
				Send(poke.Encode());
			}
		}
	}
}