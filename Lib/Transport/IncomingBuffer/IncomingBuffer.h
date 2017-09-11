#pragma once

#include <vector>
#include <queue>
#include <cstdint>

namespace Boggart
{
	namespace Transport
	{
		class IncomingBuffer
		{
		private:
			std::vector<unsigned char> m_Buffer;
			std::queue<std::vector<unsigned char>> m_MessageQueue;

		public:
			IncomingBuffer();
			~IncomingBuffer();

			void StoreIncomingData(const std::vector<unsigned char>& data);
			void ProcessIncomingData();
			std::vector<unsigned char> GetNextMessage();

		private:
			std::int32_t Find(std::uint8_t byte);
		};
	}
}
