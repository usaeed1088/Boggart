#pragma once

#include "../TransportBase.h"

#include <queue>
#include <mutex>
#include <vector>

namespace Boggart
{
	namespace Transport
	{
		class InProcess : public TransportBase
		{
		private:
			static std::vector<InProcess*> s_Subscribers;

			std::mutex m_DataQueueLock;
			std::queue<std::vector<unsigned char>> m_DataQueue;

		public:
			InProcess(std::string id);
			~InProcess() override;

		private:
			bool OnOpen() override;

			bool OnClose() override;

			bool OnSend(const std::vector<unsigned char>& data) override;

			std::vector<unsigned char> OnReceive() override;

		private:
			void Push(const std::vector<unsigned char>& data);
		};
	}
}