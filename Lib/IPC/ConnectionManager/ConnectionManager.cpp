#include "ConnectionManager.h"

#include "../Messages/Factory/Factory.h"

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
				Timer::Span_t(5000),
				Timer::Type_t::Periodic,
				std::bind(&ConnectionManager::OnProcessingTimerExpired, this)
			);

			m_TimerManager->Start(m_ProcessingTimer);
		}

		void ConnectionManager::OnIncomingMessage(std::string source, std::string destination, std::vector<unsigned char> data)
		{
			Factory factory;
			Message::IMessagePtr message = factory.CreateMessage(data);
			std::string type = message->Type();

			if (type == Request::TypeString())
			{
				OnRequest(source, destination, std::static_pointer_cast<Request>(message));
			}
			else if (type == Response::TypeString())
			{
				OnResponse(source, destination, std::static_pointer_cast<Response>(message));
			}
		}

		void ConnectionManager::OnRequest(std::string source, std::string destination, RequestPtr request)
		{			
			if (!(destination == Message::Defintion::DestinationAny || destination == m_MyId))
			{
				return;
			}
			
			if (destination == m_MyId)
			{
				// This module has considered us host
				std::int32_t index = Find(source);
				if (index == -1)
				{
					m_PeerConnections.push_back(Properties(source));
					m_Diagnostics->Log(Logger::Level::Information, "[%s] Module Added as Peer %s", m_MyId.c_str(), source.c_str());
				}
				else
				{
					m_PeerConnections[index].Attempts = 0;
				}
			}

			m_Diagnostics->Log(Logger::Level::Debug, "[%s] KeepAlive Request received from %s", m_MyId.c_str(), source.c_str());
			m_Diagnostics->Log(Logger::Level::Debug, "[%s] Sending KeepAlive Response to %s", m_MyId.c_str(), source.c_str());

			ResponsePtr response(new Response());
			m_DataSendCallback(source, response);
		}

		void ConnectionManager::OnResponse(std::string source, std::string destination, ResponsePtr response)
		{
			if (m_HostConnection.Id.empty() || destination == m_MyId)
			{
				if (m_HostConnection.Id != source)
				{
					m_Diagnostics->Log(Logger::Level::Information, "[%s] Changing host from %s to %s", m_MyId.c_str(), m_HostConnection.Id.c_str(), source.c_str());
				}

				m_HostConnection.Id = source;
				m_HostConnection.Attempts = 0;

				m_Diagnostics->Log(Logger::Level::Debug, "[%s] KeepAlive Response received from %s", m_MyId.c_str(), source.c_str());
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
				m_Diagnostics->Log(Logger::Level::Warning, "[%s] Host Connection Attempts Expired", m_MyId.c_str());
				m_HostConnection.Id = Message::Defintion::DestinationAny;
			}

			m_Diagnostics->Log(Logger::Level::Debug, "[%s] Sending KeepAlive Request to Host %s", m_MyId.c_str(), m_HostConnection.Id.c_str());

			RequestPtr request(new Request());
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
					m_Diagnostics->Log(Logger::Level::Warning, "[%s] KeepAlive attempts expired for %s", m_MyId.c_str(), it->Id.c_str());
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