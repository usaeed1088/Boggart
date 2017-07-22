#include "MessageBase.h"

#include <cstdint>

namespace Boggart
{
	namespace Message
	{
		MessageBase::MessageBase(std::string type):
			m_Type(type),
			m_Source(),
			m_Destination(),
			m_SequenceNumber(0),
			m_PayloadLength(0),
			m_Valid(true)
		{

		}

		MessageBase::MessageBase(const std::vector<unsigned char>& data):
			m_Type(0),
			m_Source(),
			m_Destination(),
			m_SequenceNumber(0),
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

		std::string MessageBase::Type()
		{
			return m_Type;
		}

		void MessageBase::Source(std::string source)
		{
			m_Source = source;
		}

		void MessageBase::Destination(std::string destination)
		{
			m_Destination = destination;
		}

		std::string MessageBase::Source()
		{
			return m_Source;
		}

		std::string MessageBase::Destination()
		{
			return m_Destination;
		}

		void MessageBase::SequenceNumber(std::uint8_t sequenceNumber)
		{
			m_SequenceNumber = sequenceNumber;
		}

		std::uint8_t MessageBase::SequenceNumber()
		{
			return m_SequenceNumber;
		}

		static void EncodeString(const std::string& string, std::vector<unsigned char>& data)
		{
			std::uint8_t size = static_cast<std::uint8_t>(string.length());

			data.push_back(size);
			data.insert(data.end(), string.begin(), string.end());
		}

		std::vector<unsigned char> MessageBase::Encode()
		{
			std::vector<unsigned char> payload = OnEncode();

			m_PayloadLength = static_cast<std::uint16_t>(payload.size());

			std::vector<unsigned char> data;

			EncodeString(m_Type, data);				// 0
			EncodeString(m_Source, data);			// 1
			EncodeString(m_Destination, data);		// 2

			data.push_back(m_SequenceNumber);		// 3

			data.push_back(m_PayloadLength >> 0);	// 4
			data.push_back(m_PayloadLength >> 8);	// 5

			data.insert(data.end(), payload.begin(), payload.end());

			return data;
		}

		static void DecodeString(std::string& string, std::vector<unsigned char>& data)
		{
			std::uint8_t size = data[0];
			
			string.insert(string.end(), data.begin() + 1, data.begin() + 1 + size);
			data.erase(data.begin(), data.begin() + 1 + size);
		}

		bool MessageBase::Decode(const std::vector<unsigned char>& data)
		{
			// NOTE: Make sure that 'data' is not referred anywhere in decoding.
			// Use '_data' instead
			std::vector<unsigned char> _data = data;

			DecodeString(m_Type, _data);				// 0
			DecodeString(m_Source, _data);				// 1
			DecodeString(m_Destination, _data);			// 2

			m_SequenceNumber = _data[0]; _data.erase(_data.begin());		// 3

			m_PayloadLength = static_cast<std::int16_t>(_data[0]) << 0;		// 4
			m_PayloadLength |= static_cast<std::int16_t>(_data[1]) << 8;	// 5

			_data.erase(_data.begin(), _data.begin() + sizeof(m_PayloadLength));

			std::vector<unsigned char> payload;

			payload.insert(payload.end(), _data.begin(), _data.begin() + m_PayloadLength);

			return OnDecode(payload);
		}
	}
}