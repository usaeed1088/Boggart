#include "ConnectionManager.h"

namespace Boggart
{
	namespace IPC
	{
		ConnectionManager::ConnectionManager(std::string myId, DataSendCallback callback):
			DependencyInjection(std::string("IPC"), std::string("ConnectionManager")),
			Subscribable(std::string("ConnectionManager")),
			m_MyId(myId),
			m_DataSendCallback(callback),
			m_HostConnection(Message::Defintion::DestinationAny),
			m_PeerConnections(),
			m_ProcessingTimer(nullptr)
		{

		}

		ConnectionManager::~ConnectionManager()
		{
			m_TimerManager->Destroy(m_ProcessingTimer);
		}

		void ConnectionManager::Start()
		{
			m_ProcessingTimer = m_TimerManager->Create
			(
				Timer::Span_t(100),
				Timer::Type_t::Periodic,
				std::bind(&ConnectionManager::OnProcessingTimerExpired, this)
			);

			m_TimerManager->Start(m_ProcessingTimer);
		}

		void ConnectionManager::OnIncomingMessage(Message::IMessagePtr message)
		{
			std::string type = message->Type();

			if (type == Request::TypeString())
			{
				OnRequest(std::static_pointer_cast<Request>(message));
			}
			else if (type == Response::TypeString())
			{
				OnResponse(std::static_pointer_cast<Response>(message));
			}
		}

		void ConnectionManager::OnRequest(RequestPtr request)
		{
			std::string source = request->Source();
			std::string destination = request->Destination();
			std::string subType = request->SubType();

			if (subType == RequestSubtypes::KeepAlive)
			{
				if (destination == Message::Defintion::DestinationAny || destination == m_MyId)
				{
					std::int32_t index = Find(source);
					if (destination == m_MyId)
					{
						// This module has considered us our master
						if (index == -1)
						{
							m_PeerConnections.push_back(Properties(source));
							m_Diagnostics->Log(Logger::Level::Information, "Module Added as Peer %s", source.c_str());
						}
						else
						{
							m_PeerConnections[index].Attempts = 0;
						}
					}

					m_Diagnostics->Log(Logger::Level::Debug, "KeepAlive Request received from %s", source.c_str());
					m_Diagnostics->Log(Logger::Level::Debug, "Sending KeepAlive Response to %s", source.c_str());

					ResponsePtr response(new Response(subType));
					m_DataSendCallback(source, response);
				}
			}
		}

		void ConnectionManager::OnResponse(ResponsePtr response)
		{
			std::string source = response->Source();
			std::string destination = response->Destination();
			std::string subType = response->SubType();

			if (subType == ResponseSubtypes::KeepAlive)
			{
				if (m_HostConnection.Id.empty() || destination == m_MyId)
				{
					m_HostConnection.Id = source;
					m_HostConnection.Attempts = 0;

					m_Diagnostics->Log(Logger::Level::Information, "KeepAlive Response received from %s", source.c_str());
				}
			}
		}

		std::int32_t ConnectionManager::Find(std::string id)
		{
			std::int32_t index = -1;

			for (std::int32_t i = 0; i < m_PeerConnections.size(); i++)
			{
				if (m_PeerConnections[i].Id == id)
				{
					index = i;
					break;
				}
			}

			return index;
		}

		void ConnectionManager::OnProcessingTimerExpired()
		{
			ProcessHostConnection();
			ProcessPeerConnections();
		}

		void ConnectionManager::ProcessHostConnection()
		{
			m_HostConnection.Attempts++;
			// TODO: Get Max. Attempts from Configuration
			const std::int32_t MaxAttempts = 3;
			if (m_HostConnection.Attempts > MaxAttempts)
			{
				m_HostConnection.Id = Message::Defintion::DestinationAny;
			}

			m_Diagnostics->Log(Logger::Level::Debug, "Sending KeepAlive Request to Host %s", m_HostConnection.Id.c_str());

			RequestPtr request(new Request(RequestSubtypes::KeepAlive));
			m_DataSendCallback(m_HostConnection.Id, request);
		}

		void ConnectionManager::ProcessPeerConnections()
		{
			const std::int32_t MaxAttempts = 3;

			for (std::vector<Properties>::iterator it = m_PeerConnections.begin(); it != m_PeerConnections.end();)
			{
				it->Attempts++;
				if (it->Attempts > MaxAttempts)
				{
					m_Diagnostics->Log(Logger::Level::Warning, "KeepAlive attempts expired for %s", it->Id.c_str());
					it = m_PeerConnections.erase(it);
				}
				else
				{
					it++;
				}
			}
		}
	}
}