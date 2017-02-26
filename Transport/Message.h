#pragma once

#include "Type.h"

namespace Transport
{
	class Message
	{
	public:
		enum class Type : Transport::Type::Byte
		{
			Unknown,
			Request,
			Receipt,
		};

	private:
		// Data members
		Transport::Type::Id			m_Source;
		Transport::Type::Id			m_Destination;
		Transport::Type::Sequence	m_Sequence;
		Transport::Message::Type	m_Type;
		Transport::Type::Size		m_PayloadSize;
		Transport::Type::Bytes		m_Payload;

		// Meta data
		bool m_Valid;

	public:
		Message(Transport::Type::Id source, Transport::Type::Id destination, Transport::Type::Sequence sequence,
			Transport::Message::Type type);

		Message(Transport::Type::Id source, Transport::Type::Id destination, Transport::Type::Sequence sequence,
			Transport::Message::Type type, const Transport::Type::Bytes& payload);

		Message(const Transport::Type::Bytes& data);

		bool Valid() const;

		Transport::Type::Id Source() const;
		Transport::Type::Id Destination() const;
		Transport::Type::Sequence Sequence() const;
		Transport::Message::Type MessageType() const;
		Transport::Type::Bytes Payload() const;

		Transport::Type::Bytes Encode() const;

	private:
		bool Decode(const Transport::Type::Bytes& data);
	};
}