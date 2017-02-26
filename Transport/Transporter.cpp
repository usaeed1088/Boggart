#include "Transporter.h"

namespace Transport
{
	Transporter::Transporter(Type::Id id, const Physical& physical):
		m_Id(id),
		m_Physical(physical)
	{

	}

	void Transporter::Send(Type::Id destination, const Type::Bytes& data, bool guaranteedDelivery)
	{
		Type::Sequence sequence = GenerateSequence();
		Message message(m_Id, destination, sequence, Message::Type::Request, data);

		// TODO: Push to queue for Receipt processing and retransmission
		m_Physical.Send(message.Encode());
	}

	Type::Bytes Transporter::Receive(Type::Id source)
	{
		Type::Bytes data = m_Physical.Receive();
		Message message(data);

		if (!message.Valid())
		{
			return Type::Bytes();
		}

		switch (message.MessageType())
		{
		case Message::Type::Request:
			return OnRequest(message, source);
			break;
		case Message::Type::Receipt:
			return OnReceipt(message, source);
			break;
		}	

		return Type::Bytes();
	}

	Type::Bytes Transporter::OnRequest(const Message& message, Type::Id source)
	{
		if (message.Destination() == m_Id)
		{
			SendReceipt(message);
		}

		if (message.Source() == source)
		{
			return message.Payload();
		}

		return Type::Bytes();
	}

	Type::Bytes Transporter::OnReceipt(const Message& message, Type::Id source)
	{
		// TODO: Process receipts
		return Type::Bytes();
	}

	Type::Sequence Transporter::GenerateSequence()
	{
		static Type::Sequence seq = 0;	seq++;	return seq;
	}

	void Transporter::SendReceipt(const Message& message)
	{
		Message receipt(m_Id, message.Source(), message.Sequence(), Message::Type::Receipt);
		m_Physical.Send(receipt.Encode());
	}
}