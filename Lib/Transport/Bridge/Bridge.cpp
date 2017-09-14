#include "Bridge.h"

namespace Boggart
{
	namespace Transport
	{
		Bridge::Bridge():
			TransportBase(std::string("Bridge"), std::string("")), // Bridge has no id of its own
			m_Transports(),
			m_ProcessingTimer(nullptr)
		{

		}

		Bridge::~Bridge()
		{
			Close();
		}

		void Bridge::InjectTransport(std::shared_ptr<TransportBase> transport)
		{
			m_Transports.push_back(transport);
		}

		bool Bridge::OnOpen()
		{
			m_ProcessingTimer = m_TimerManager->Create
			(
				Timer::Span_t(50),
				Timer::Type_t::Periodic,
				std::bind(&Bridge::OnProcessingTimerExpired, this)
			);

			bool ret = true;

			for (std::shared_ptr<TransportBase> transport : m_Transports)
			{
				m_Diagnostics->ShareLogger(transport);
				transport->InjectDependency(m_TimerManager);
				ret &= transport->Open();
			}

			ret &= m_TimerManager->Start(m_ProcessingTimer);

			return ret;
		}

		bool Bridge::OnClose()
		{
			return m_TimerManager->Destroy(m_ProcessingTimer);
		}

		bool Bridge::OnSend(const std::vector<unsigned char>& data)
		{
			// Bridge cannot 'initiate' a send
			return false;
		}

		std::vector<unsigned char> Bridge::OnReceive()
		{
			return std::vector<unsigned char>();
		}

		void Bridge::OnProcessingTimerExpired()
		{
			for (std::size_t i = 0; i < m_Transports.size(); i++)
			{
				// Receive data from one transport
				std::vector<unsigned char> data = m_Transports[i]->Receive();

				if (data.empty())
				{
					continue;
				}

				// Send it to all the others
				for (std::size_t j = 0; j < m_Transports.size(); j++)
				{
					if (i != j)
					{
						m_Transports[j]->Send(data);
					}
				}
			}
		}
	}
}