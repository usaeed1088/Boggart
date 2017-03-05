#include "Transporter.h"

namespace Transport
{
	Transporter::Transporter(DataType::Id id, const Physical& physical):
		m_Id(id),
		m_Physical(physical),
		m_IncomingMessages()
	{

	}

	void Transporter::Process()
	{
		// TODO: Process Heartbeats
		// TODO: Process Retransmissions
		m_Physical.Process();
		ProcessIncoming();
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
		if (m_IncomingMessages.empty())
		{
			return DataType::Bytes();
		}

		DataType::Bytes data;
		std::list<Message>::iterator removable;

		for (std::list<Message>::iterator it = m_IncomingMessages.begin(); it != m_IncomingMessages.end(); ++it)
		{
			if (it->Source() == source)
			{
				data = it->Payload();
				removable = it;
				break;
			}
		}

		m_IncomingMessages.erase(removable);
		return data;
	}

	void Transporter::ProcessIncoming()
	{
		DataType::Bytes data = m_Physical.Receive();
		Message message(data);

		if (!message.Valid())
		{
			return;
		}

		switch (message.MessageType())
		{
		case Message::Type::Request:
			OnRequest(message);
			break;
		case Message::Type::Receipt:
			OnReceipt(message);
			break;
		}
	}

	void Transporter::OnRequest(const Message& message)
	{
		if (message.Destination() == m_Id)
		{
			SendReceipt(message);
		}

		m_IncomingMessages.push_back(message);
	}

	void Transporter::OnReceipt(const Message& message)
	{
		// TODO: Process receipts
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