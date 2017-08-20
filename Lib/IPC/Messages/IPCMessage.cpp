#include "IPCMessage.h"

#include <Message/Utility/Utility.h>

namespace Boggart
{
	namespace IPC
	{
		IPCMessage::IPCMessage(std::string type):
			Message::MessageBase(type),
			m_Source(),
			m_Destination(),
			m_SequenceNumber(0),
			m_ApplicationPayload(),
			m_Valid(true)
		{

		}

		IPCMessage::IPCMessage(const std::vector<unsigned char>& data):
			Message::MessageBase(data),
			m_Source(),
			m_Destination(),
			m_SequenceNumber(0),
			m_ApplicationPayload(),
			m_Valid(false)
		{
			if (Decode(data))
			{
				m_Valid = true;
			}
		}

		IPCMessage::~IPCMessage()
		{

		}

		bool IPCMessage::Valid()
		{
			return m_Valid;
		}

		void IPCMessage::Source(std::string source)
		{
			m_Source = source;
		}

		void IPCMessage::Destination(std::string destination)
		{
			m_Destination = destination;
		}

		std::string IPCMessage::Source()
		{
			return m_Source;
		}

		std::string IPCMessage::Destination()
		{
			return m_Destination;
		}

		void IPCMessage::SequenceNumber(std::uint8_t sequenceNumber)
		{
			m_SequenceNumber = sequenceNumber;
		}

		std::uint8_t IPCMessage::SequenceNumber()
		{
			return m_SequenceNumber;
		}

		void IPCMessage::ApplicationPayload(const std::vector<unsigned char>& payload)
		{
			m_ApplicationPayload = payload;
		}

		std::vector<unsigned char> IPCMessage::ApplicationPayload()
		{
			return m_ApplicationPayload;
		}

		std::vector<unsigned char> IPCMessage::OnEncode()
		{
			std::vector<unsigned char> data;

			data.push_back(m_SequenceNumber);						// 0

			Message::Utility::EncodeString(m_Source, data);			// 1
			Message::Utility::EncodeString(m_Destination, data);	// 2
			Message::Utility::EncodeVector(m_ApplicationPayload, data);	// 3

			return data;
		}

		bool IPCMessage::OnDecode(const std::vector<unsigned char>& data)
		{
			// NOTE: Make sure that 'data' is not referred anywhere in decoding.
			// Use '_data' instead
			std::vector<unsigned char> _data = data;

			m_SequenceNumber = _data[0];							// 0
			_data.erase(_data.begin());

			Message::Utility::DecodeString(m_Source, _data);		// 1
			Message::Utility::DecodeString(m_Destination, _data);	// 2
			Message::Utility::DecodeVector(m_ApplicationPayload, _data);	// 3

			return true;
		}
	}
}