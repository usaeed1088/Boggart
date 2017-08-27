#include "DisciplineBase.h"

namespace Boggart
{
	namespace Transport
	{
		DisciplineBase::DisciplineBase(std::string id, std::string moduleName):
			TransportBase(moduleName, id),
			m_Transport(nullptr),
			m_ProcessingTimer(nullptr),
			m_IncomingQueue(),
			m_OutgoingQueue()
		{

		}

		DisciplineBase::~DisciplineBase()
		{
			Close();
		}

		void DisciplineBase::InjectTransport(ITransportPtr transport)
		{
			m_Transport = transport;
		}

		bool DisciplineBase::OnOpen()
		{
			m_Diagnostics->Log(Logger::Level::Information, "Opening");

			m_ProcessingTimer = m_TimerManager->Create
			(
				Timer::Span_t(50),
				Timer::Type_t::Periodic,
				std::bind(&DisciplineBase::OnProcessingTimerExpired, this)
			);

			bool ret = true;

			ret &= m_TimerManager->Start(m_ProcessingTimer);
			ret &= _OnOpen();

			return ret;
		}

		bool DisciplineBase::OnClose()
		{
			m_Diagnostics->Log(Logger::Level::Information, "Closing");

			bool ret = true;

			ret &= m_TimerManager->Destroy(m_ProcessingTimer);
			ret &= _OnClose();

			return ret;
		}

		bool DisciplineBase::OnSend(const std::vector<unsigned char>& data)
		{
			m_OutgoingQueue.push(data);

			m_Diagnostics->Log(Logger::Level::Debug, "Queueing data of size: %d. Outgoing Queue size: %d", data.size(), m_OutgoingQueue.size());

			return true;
		}

		std::vector<unsigned char> DisciplineBase::OnReceive()
		{
			if (m_IncomingQueue.empty())
			{
				return std::vector<unsigned char>();
			}

			std::vector<unsigned char> data = m_IncomingQueue.front();

			m_Diagnostics->Log(Logger::Level::Debug, "Received data of size %d. Incoming Queue size: %d", data.size(), m_IncomingQueue.size());

			m_IncomingQueue.pop();

			return data;
		}

		void DisciplineBase::OnProcessingTimerExpired()
		{
			std::vector<unsigned char> data = m_Transport->Receive();

			while (!data.empty())
			{
				Message::IMessagePtr message = m_Factory.CreateMessage(data);

				if (message)
				{
					if (message->Type() == Ping::TypeString())
					{
						OnPing(std::static_pointer_cast<Ping>(message));
					}
					else if (message->Type() == Pong::TypeString())
					{
						OnPong(std::static_pointer_cast<Pong>(message));
					}
				}

				data = m_Transport->Receive();
			}
		}

		bool DisciplineBase::SentToTransport(const std::vector<unsigned char>& data)
		{
			return m_Transport->Send(data);
		}
	}
}