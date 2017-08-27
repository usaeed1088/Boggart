#pragma once

#include "IDiscipline.h"

#include "../TransportBase.h"

#include "Messages/Ping/Ping.h"
#include "Messages/Pong/Pong.h"

#include "Messages/Factory/Factory.h"

#include <Common/Patterns/DependencyInjection/DependencyInjection.h>

#include <queue>
#include <vector>

namespace Boggart
{
	namespace Transport
	{
		class DisciplineBase : public IDiscipline, public TransportBase
		{
		private:
			ITransportPtr m_Transport;
			Factory m_Factory;

			Timer::IDevicePtr m_ProcessingTimer;

		protected:
			std::queue<std::vector<unsigned char>> m_IncomingQueue;
			std::queue<std::vector<unsigned char>> m_OutgoingQueue;

		protected:
			DisciplineBase(std::string id, std::string moduleName);

		public:
			virtual ~DisciplineBase() override;

			void InjectTransport(ITransportPtr transport);

		private:
			bool OnOpen() override;

			bool OnClose() override;

			bool OnSend(const std::vector<unsigned char>& data) override;

			std::vector<unsigned char> OnReceive() override;

		private:
			void OnProcessingTimerExpired();

		protected:
			bool SentToTransport(const std::vector<unsigned char>& data);

		protected:
			virtual bool _OnOpen() = 0;

			virtual bool _OnClose() = 0;

			virtual void OnPing(PingPtr ping) = 0;

			virtual void OnPong(PongPtr pong) = 0;
		};
	}
}