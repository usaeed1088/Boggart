#include "Moderator.h"

namespace Boggart
{
	namespace Transport
	{
		Moderator::Moderator(std::string id):
			DisciplineBase(std::string("Moderator"), id)
		{

		}

		Moderator::~Moderator()
		{

		}

		void Moderator::OnPingTimerExpired()
		{

		}

		bool Moderator::_OnOpen()
		{
			m_PingTimer = m_TimerManager->Create
			(
				Timer::Span_t(5000),
				Timer::Type_t::Periodic,
				std::bind(&Moderator::OnPingTimerExpired, this)
			);

			return m_TimerManager->Start(m_PingTimer);
		}

		bool Moderator::_OnClose()
		{
			return m_TimerManager->Destroy(m_PingTimer);
		}

		void Moderator::OnPing(PingPtr ping)
		{
			m_Diagnostics->Log(Logger::Level::Error, "Received Ping");
		}

		void Moderator::OnPong(PongPtr pong)
		{
			m_Diagnostics->Log(Logger::Level::Debug, "Received Pong");
		}
	}
}