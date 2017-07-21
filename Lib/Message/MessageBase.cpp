#include "MessageBase.h"

namespace Boggart
{
	namespace Message
	{
		MessageBase::MessageBase(std::int16_t type):
			m_Type(type),
			m_PayloadLength(0),
			m_Valid(true)
		{

		}

		MessageBase::MessageBase(const std::vector<unsigned char>& data):
			m_Type(0),
			m_PayloadLength(0),
			m_Valid(false)
		{
			if (Decode(data))
			{
				m_Valid = true;
			}
		}

		MessageBase::~MessageBase()
		{

		}

		bool MessageBase::Valid()
		{
			return m_Valid;
		}

		std::int16_t MessageBase::Type()
		{
			return m_Type;
		}

		std::vector<unsigned char> MessageBase::Encode()
		{
			std::vector<unsigned char> payload = OnEncode();

			m_PayloadLength = payload.size();

			// Start Encoding
			std::vector<unsigned char> data;

			data.push_back(m_Type >> 0);			// 0
			data.push_back(m_Type >> 8);			// 1

			data.push_back(m_PayloadLength >> 0);	// 2
			data.push_back(m_PayloadLength >> 8);	// 3

			data.insert(data.end(), payload.begin(), payload.end());

			return data;
		}


		bool MessageBase::Decode(const std::vector<unsigned char>& data)
		{
			m_Type = static_cast<std::int16_t>(data[0]) << 0;
			m_Type |= static_cast<std::int16_t>(data[1]) << 8;

			m_PayloadLength = static_cast<std::int16_t>(data[2]) << 0;
			m_PayloadLength |= static_cast<std::int16_t>(data[3]) << 8;

			std::vector<unsigned char> payload;

			payload.insert(payload.end(), data.begin() + 4, data.begin() + 4 + m_PayloadLength);

			return OnDecode(payload);
		}
	}
}