#pragma once

#include "../IPCBase.h"

#include <queue>

namespace Boggart
{
	namespace IPC
	{
		class Asynchronous : public IPCBase
		{
		private:
			Timer::IDevicePtr m_ProcessingTimer;

			std::queue<std::vector<unsigned char>> m_OutgoingQueue;
			std::queue<std::vector<unsigned char>> m_IncomingQueue;

		public:
			Asynchronous(std::string myId);
			~Asynchronous() override;

		private:
			bool OnStart() override;
			bool OnSend(IPCMessagePtr message) override;

			void OnProcessingTimerExpired();

			void ProcessIncomingTransport();
			void ProcessOutgoingQueue();
			void ProcessIncomingQueue();
		};
	}
}