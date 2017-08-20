#include "MessageBase.h"

#include <Message/Utility/Utility.h>

namespace Boggart
{
	namespace IPC
	{
		MessageBase::MessageBase(std::string type):
			Message::MessageBase(type),
			m_Type(type),
			m_Source(),
			m_Destination(),
			m_SequenceNumber(0),
			m_ApplicationPayload(),
			m_Valid(true)
		{

		}

		MessageBase::MessageBase(const std::vector<unsigned char>& data):
			Message::MessageBase(data), 
			m_Type(),
			m_Source(),
			m_Destination(),
			m_SequenceNumber(0),
			m_ApplicationPayload(),
			m_Valid(false)
		{

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

		void MessageBase::ApplicationPayload(const std::vector<unsigned char>& payload)
		{
			m_ApplicationPayload = payload;
		}

		std::vector<unsigned char> MessageBase::ApplicationPayload()
		{
			return m_ApplicationPayload;
		}

		std::vector<unsigned char> MessageBase::OnEncode()
		{
			std::vector<unsigned char> messageData = _OnEncode();
			std::vector<unsigned char> data;

			data.push_back(m_SequenceNumber);						// 0

			Message::Utility::EncodeString(m_Type, data);			// 1
			Message::Utility::EncodeString(m_Source, data);			// 2
			Message::Utility::EncodeString(m_Destination, data);	// 3
			Message::Utility::EncodeVector(m_ApplicationPayload, data);	// 4
			Message::Utility::EncodeVector(messageData, data);			// 5

			return data;
		}

		bool MessageBase::OnDecode(const std::vector<unsigned char>& data)
		{
			// NOTE: Make sure that 'data' is not referred anywhere in decoding.
			// Use '_data' instead
			std::vector<unsigned char> _data = data;
			std::vector<unsigned char> messageData;

			m_SequenceNumber = _data[0];							// 0
			_data.erase(_data.begin());

			Message::Utility::DecodeString(m_Type, _data);			// 1
			Message::Utility::DecodeString(m_Source, _data);		// 2
			Message::Utility::DecodeString(m_Destination, _data);	// 3
			Message::Utility::DecodeVector(m_ApplicationPayload, _data);	// 4
			Message::Utility::DecodeVector(messageData, _data);				// 5

			return _OnDecode(messageData);
		}
	}
}