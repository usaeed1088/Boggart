#include "Message.h"

namespace Transport
{
	Message::Message(Transport::Type::Id source, Transport::Type::Id destination, Transport::Type::Sequence sequence,
		Transport::Message::Type type):
		m_Source(source), m_Destination(destination), m_Sequence(sequence), m_Type(type), m_PayloadSize(0), m_Payload(),
		m_Valid(false)
	{

	}

	Message::Message(Transport::Type::Id source, Transport::Type::Id destination, Transport::Type::Sequence sequence,
		Transport::Message::Type type, const Transport::Type::Bytes& payload):
		m_Source(source), m_Destination(destination), m_Sequence(sequence), m_Type(type), m_PayloadSize(payload.size()), m_Payload(payload),
		m_Valid(false)
	{

	}

	Message::Message(const Transport::Type::Bytes& data):
		m_Source(0), m_Destination(0), m_Sequence(0), m_Type(Type::Unknown), m_PayloadSize(0), m_Payload(),
		m_Valid(false)
	{
		if (Decode(data))
		{
			m_Valid = true;
		}
	}

	bool Message::Valid() const
	{
		return m_Valid;
	}

	Transport::Type::Id Message::Source() const
	{
		return m_Source;
	}

	Transport::Type::Id Message::Destination() const
	{
		return m_Destination;
	}

	Transport::Type::Sequence Message::Sequence() const
	{
		return m_Sequence;
	}

	Transport::Message::Type Message::MessageType() const
	{
		return m_Type;
	}

	Transport::Type::Bytes Message::Payload() const
	{
		return m_Payload;
	}

	template<class T>
	static void Append(Transport::Type::Bytes& data, T value)
	{
		Transport::Type::Bytes bytes;

		for (Type::Size i = 0; i < sizeof(value); i++)
		{
			bytes.push_back(value >> (i * 8));
		}

		data.insert(data.end(), bytes.begin(), bytes.end());
	}

	Transport::Type::Bytes Message::Encode() const
	{
		Transport::Type::Bytes data;

		Append(data, m_Source);
		Append(data, m_Destination);
		Append(data, m_Sequence);
		Append(data, static_cast<Transport::Type::Byte>(m_Type));
		Append(data, m_PayloadSize);

		for (Transport::Type::Byte b : m_Payload)
		{
			data.push_back(b);
		}

		return data;
	}

	template <class T>
	static T Subtract(Transport::Type::Bytes& data)
	{
		T value = 0;

		for (Type::Size i = 0; i < sizeof(value); i++)
		{
			value |= static_cast<T>(data[i]) << (i * 8);
		}

		data.erase(data.begin(), data.begin() + sizeof(value));
		return value;
	}

	bool Message::Decode(const Transport::Type::Bytes& data)
	{
		const Transport::Type::Size HeaderLength =
			sizeof(m_Source) + sizeof(m_Destination) + sizeof(m_Sequence) + sizeof((Transport::Type::Byte)m_Type) + sizeof(m_PayloadSize);

		if (data.size() < HeaderLength)
		{
			return false;
		}

		Transport::Type::Bytes bytes = data;

		m_Source		= Subtract<Transport::Type::Id>(bytes);
		m_Destination	= Subtract<Transport::Type::Id>(bytes);
		m_Sequence		= Subtract<Transport::Type::Sequence>(bytes);
		m_Type			= static_cast<Message::Type>(Subtract<Transport::Type::Byte>(bytes));
		m_PayloadSize	= Subtract<Transport::Type::Size>(bytes);

		if (bytes.size() < m_PayloadSize)
		{
			return false;
		}

		m_Payload.assign(bytes.begin(), bytes.begin() + m_PayloadSize);

		return true;
	}
}