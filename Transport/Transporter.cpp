#include "Transporter.h"

namespace Transport
{
	Transporter::Transporter(DataType::Id id, const Physical& physical):
		m_Id(id),
		m_Physical(physical)
	{

	}

	void Transporter::Send(DataType::Id destination, const DataType::Bytes& data, bool guaranteedDelivery)
	{
		DataType::Sequence sequence = GenerateSequence();
		Message message(m_Id, destination, sequence, Message::Type::Request, data);

		// TODO: Push to queue for Receipt processing and retransmission
		m_Physical.Send(message.Encode());
	}

	DataType::Bytes Transporter::Receive(DataType::Id source)
	{
		DataType::Bytes data = m_Physical.Receive();
		Message message(data);

		if (!message.Valid())
		{
			return DataType::Bytes();
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

		return DataType::Bytes();
	}

	DataType::Bytes Transporter::OnRequest(const Message& message, DataType::Id source)
	{
		if (message.Destination() == m_Id)
		{
			SendReceipt(message);
		}

		if (message.Source() == source)
		{
			return message.Payload();
		}

		return DataType::Bytes();
	}

	DataType::Bytes Transporter::OnReceipt(const Message& message, DataType::Id source)
	{
		// TODO: Process receipts
		return DataType::Bytes();
	}

	DataType::Sequence Transporter::GenerateSequence()
	{
		static DataType::Sequence seq = 0;	seq++;	return seq;
	}

	void Transporter::SendReceipt(const Message& message)
	{
		Message receipt(m_Id, message.Source(), message.Sequence(), Message::Type::Receipt);
		m_Physical.Send(receipt.Encode());
	}
}