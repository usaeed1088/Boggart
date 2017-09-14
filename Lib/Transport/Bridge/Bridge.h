#pragma once

#include "../TransportBase.h"

namespace Boggart
{
	namespace Transport
	{
		class Bridge : public TransportBase
		{
		private:
			std::vector<std::shared_ptr<TransportBase>> m_Transports;
			Timer::IDevicePtr m_ProcessingTimer;

		public:
			Bridge();
			~Bridge() override;

			void InjectTransport(std::shared_ptr<TransportBase> transport);

		private:
			bool OnOpen() override;
			bool OnClose() override;
			bool OnSend(const std::vector<unsigned char>& data) override;
			std::vector<unsigned char> OnReceive() override;

		private:
			void OnProcessingTimerExpired();
		};
	}
}