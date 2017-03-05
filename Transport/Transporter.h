#pragma once

#include "DataType.h"
#include "Message.h"
#include "Physical/Physical.h"

namespace Transport
{
	class Transporter
	{
	public:
		static const DataType::Id BROADCAST = 0;

	private:
		DataType::Id m_Id;
		const Physical& m_Physical;

		std::list<Message> m_IncomingMessages;

	public:
		Transporter(DataType::Id id, const Physical& physical);
		
		void Process();

		void Send(DataType::Id destination, const DataType::Bytes& data, bool guaranteedDelivery);
		DataType::Bytes Receive(DataType::Id source);

	private:
		void ProcessIncoming();

	private:
		void OnRequest(const Message& message);
		void OnReceipt(const Message& message);

	private:
		void SendReceipt(const Message& message);

	private:
		DataType::Sequence GenerateSequence();
	};
}
