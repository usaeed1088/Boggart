#include "IncomingBuffer.h"

#include "../Definition/Definition.h"

namespace Boggart
{
	namespace Transport
	{
		IncomingBuffer::IncomingBuffer():
			m_Buffer(),
			m_MessageQueue()
		{

		}

		IncomingBuffer::~IncomingBuffer()
		{

		}

		void IncomingBuffer::StoreIncomingData(const std::vector<unsigned char>& data)
		{
			m_Buffer.insert(m_Buffer.end(), data.begin(), data.end());
		}

		void IncomingBuffer::ProcessIncomingData()
		{
			std::int32_t SOPIndex = Find(Definition::SOP);

			if (SOPIndex == -1)
			{
				// SOP not found
				m_Buffer.clear();
				return;
			}

			if (SOPIndex > 0)
			{
				m_Buffer.erase(m_Buffer.begin() + (SOPIndex - 1)); // Preserve the SOP
			}

			int EOPIndex = Find(Definition::EOP);

			if (EOPIndex > 0)
			{
				std::vector<unsigned char> message(m_Buffer.begin(), m_Buffer.begin() + (EOPIndex + 1));
				m_MessageQueue.push(message);
				m_Buffer.erase(m_Buffer.begin(), m_Buffer.begin() + EOPIndex);
			}
		}

		std::vector<unsigned char> IncomingBuffer::GetNextMessage()
		{
			if (m_MessageQueue.empty())
			{
				return std::vector<unsigned char>();
			}

			std::vector<unsigned char> message = m_MessageQueue.front();
			m_MessageQueue.pop();
			return message;
		}

		std::int32_t IncomingBuffer::Find(std::uint8_t byte)
		{
			std::int32_t index = -1;
			for (std::uint32_t i = 0; i < m_Buffer.size(); i++)
			{
				if (m_Buffer[i] == byte)
				{
					index = i;
					break;
				}
			}

			return index;
		}
	}
}