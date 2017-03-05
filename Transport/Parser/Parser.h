#pragma once

#include "../DataType.h"

namespace Transport
{
	class Parser
	{
	private:
		static const DataType::Byte EscapeCharacter;
		static const DataType::Byte SOP;
		static const DataType::Byte EOP;

	public:
		static DataType::Bytes Escape(const DataType::Bytes& data);
		static DataType::Bytes Unescape(const DataType::Bytes& data);
		static DataType::Bytes Wrap(const DataType::Bytes& data);
		static DataType::Bytes Unwrap(const DataType::Bytes& data);

	private:
		DataType::Bytes m_Buffer;
		DataType::Queue m_IncomingMessages;

	public:
		void ProcessIncomingData(const DataType::Bytes& data);
		DataType::Bytes GetIncomingMessage();

	private:
		DataType::Size Find(DataType::Byte byte);
	};
}