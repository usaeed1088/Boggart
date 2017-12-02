#include "Server.h"

#include "../Definition/Definition.h"
#include "../../Helper/Helper.h"

#include <Lib/Instantiator.h>
#include <Message/Types/Generic/Generic.h>

namespace Boggart
{
	namespace Transport
	{
		namespace UDP
		{
			Server::Server(std::string myId, std::int32_t port) :
				TransportBase(std::string("UDPServer"), myId),
				m_Port(port),
				m_Socket(PAL::Instantiator::ObjectFactory()->CreateSocket(PAL::Object::SocketType::Datagram, PAL::Object::SocketFamily::Internetwork)),
				m_ProcessingTimer(nullptr),
				m_IncomingQueue(),
				m_Peers()
			{
				
			}

			Server::~Server()
			{
				Close();
			}

			bool Server::OnOpen()
			{
				bool ret = true;

				ret &= m_Socket->Open();
				ret &= m_Socket->Bind(m_Port);
				ret &= m_Socket->SetNonBlocking();

				if (ret)
				{
					// TODO: Get span from configuration or not. Think about it?
					m_ProcessingTimer = m_TimerManager->Create
					(
						Timer::Span_t(50),
						Timer::Type_t::Periodic,
						std::bind(&Server::OnProcessingTimerExpired, this)
					);
					m_TimerManager->Start(m_ProcessingTimer);
				}

				return ret;
			}

			bool Server::OnClose()
			{
				bool ret = true;

				m_TimerManager->Destroy(m_ProcessingTimer);

				m_Socket->Close();

				return ret;
			}

			bool Server::OnSend(const std::vector<unsigned char>& data)
			{
				bool ret = true;

				for (std::size_t i = 0; i < m_Peers.size(); i++)
				{
					ret &= m_Socket->SendTo(m_Peers[i].IP, m_Peers[i].Port, data);
				}

				return ret;
			}

			std::vector<unsigned char> Server::OnReceive()
			{
				if (m_IncomingQueue.empty())
				{
					return std::vector<unsigned char>();
				}

				std::vector<unsigned char> data = m_IncomingQueue.front();
				m_IncomingQueue.pop();
				return data;
			}

			void Server::OnProcessingTimerExpired()
			{
				ProcessAsynchronousIncoming();
			}

			void Server::ProcessAsynchronousIncoming()
			{
				std::string source;
				std::int32_t port;

				std::vector<unsigned char> data = m_Socket->ReceiveFrom(source, port);

				if (data.empty())
				{
					return;
				}

				if (IsPokeMessage(data))
				{
					AddToListIfNotPresent(source, port);
				}
				else
				{
					std::int32_t i = FindIndexOf(source, port);

					for (std::size_t j = 0; j < m_Peers.size(); j++)
					{
						if (i == j)
						{
							continue;
						}

						m_Socket->SendTo(m_Peers[j].IP, m_Peers[j].Port, data);
					}

					m_IncomingQueue.push(data);
				}
			}

			std::int32_t Server::FindIndexOf(std::string source, std::int32_t port)
			{
				for (std::int32_t i = 0; i < m_Peers.size(); i++)
				{
					if (m_Peers[i].IP == source, m_Peers[i].Port == port)
					{
						return i;
					}
				}
				return -1;
			}

			bool Server::IsPokeMessage(const std::vector<unsigned char>& data)
			{
				// TODO: This is a highly unwanted implementation
				// Find a better solution for this. Unwrapping and Wrapping 
				// should be done only in TransportBase
				std::vector<unsigned char> unwrapped = Helper::Unwrap(data);

				Message::Type::Generic poke(unwrapped);

				if (!poke.Valid())
				{
					return false;
				}

				if (poke.Type() == Definition::PokeMessage)
				{
					return true;
				}

				return false;
			}

			void Server::AddToListIfNotPresent(std::string source, std::int32_t port)
			{
				bool present = false;

				for (std::size_t i = 0; i < m_Peers.size(); i++)
				{
					if (m_Peers[i].IP == source && m_Peers[i].Port == port)
					{
						present = true;
						break;
					}
				}

				if (!present)
				{
					m_Peers.push_back(Peer(source, port));
				}
			}
		}
	}
}