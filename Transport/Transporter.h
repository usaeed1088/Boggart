#pragma once

#include "Type.h"
#include "Message.h"
#include "Physical/Physical.h"

namespace Transport
{
	class Transporter
	{
	public:
		static const Type::Id BROADCAST = 0;

	private:
		Type::Id m_Id;
		const Physical& m_Physical;

	public:
		Transporter(Type::Id id, const Physical& physical);
		
		void Send(Type::Id destination, const Type::Bytes& data, bool guaranteedDelivery);
		Type::Bytes Receive(Type::Id source);

	private:
		Type::Bytes OnRequest(const Message& message, Type::Id source);
		Type::Bytes OnReceipt(const Message& message, Type::Id source);

	private:
		void SendReceipt(const Message& message);

	private:
		Type::Sequence GenerateSequence();
	};
}
