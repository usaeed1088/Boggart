#pragma once

#include "../DisciplineBase.h"

namespace Boggart
{
	namespace Transport
	{
		class Moderator : public DisciplineBase
		{
		private:
			Timer::IDevicePtr m_PingTimer;

		public:
			Moderator(std::string id);
			~Moderator() override;

		private:
			void OnPingTimerExpired();

		private:
			bool _OnOpen() override;

			bool _OnClose() override;

			void OnPing(PingPtr ping) override;

			void OnPong(PongPtr pong) override;
		};
	}
}