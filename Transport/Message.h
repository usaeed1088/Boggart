#pragma once

#include "DataType.h"

namespace Transport
{
	class Message
	{
	public:
		enum class Type : Transport::DataType::Byte
		{
			Unknown,
			Request,
			Receipt,
		};

	private:
		// Data members
		Transport::DataType::Id			m_Source;
		Transport::DataType::Id			m_Destination;
		Transport::DataType::Sequence	m_Sequence;
		Transport::Message::Type		m_Type;
		Transport::DataType::Size		m_PayloadSize;
		Transport::DataType::Bytes		m_Payload;

		// Meta data
		bool m_Valid;

	public:
		Message(Transport::DataType::Id source, Transport::DataType::Id destination, Transport::DataType::Sequence sequence,
			Transport::Message::Type type);

		Message(Transport::DataType::Id source, Transport::DataType::Id destination, Transport::DataType::Sequence sequence,
			Transport::Message::Type type, const Transport::DataType::Bytes& payload);

		Message(const Transport::DataType::Bytes& data);

		bool Valid() const;

		Transport::DataType::Id Source() const;
		Transport::DataType::Id Destination() const;
		Transport::DataType::Sequence Sequence() const;
		Transport::Message::Type MessageType() const;
		Transport::DataType::Bytes Payload() const;

		Transport::DataType::Bytes Encode() const;

	private:
		bool Decode(const Transport::DataType::Bytes& data);
	};
}