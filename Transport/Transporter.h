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

	public:
		Transporter(DataType::Id id, const Physical& physical);
		
		void Send(DataType::Id destination, const DataType::Bytes& data, bool guaranteedDelivery);
		DataType::Bytes Receive(DataType::Id source);

	private:
		DataType::Bytes OnRequest(const Message& message, DataType::Id source);
		DataType::Bytes OnReceipt(const Message& message, DataType::Id source);

	private:
		void SendReceipt(const Message& message);

	private:
		DataType::Sequence GenerateSequence();
	};
}
