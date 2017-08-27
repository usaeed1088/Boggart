#include "Moderated.h"

namespace Boggart
{
	namespace Transport
	{
		Moderated::Moderated(std::string id):
			DisciplineBase(std::string("Moderated"), id)
		{

		}

		Moderated::~Moderated()
		{

		}

		bool Moderated::_OnOpen()
		{
			return true;
		}

		bool Moderated::_OnClose()
		{
			return true;
		}

		void Moderated::OnPing(PingPtr ping)
		{
			m_Diagnostics->Log(Logger::Level::Debug, "Received Ping");
		}

		void Moderated::OnPong(PongPtr pong)
		{
			m_Diagnostics->Log(Logger::Level::Error, "Received Pong");
		}
	}
}