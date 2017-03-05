#include "Parser.h"

namespace Transport
{
	const DataType::Byte Parser::EscapeCharacter('\\');
	const DataType::Byte Parser::SOP('[');
	const DataType::Byte Parser::EOP(']');

	DataType::Bytes Parser::Escape(const DataType::Bytes& data)
	{
		DataType::Bytes escaped;

		for (DataType::Size i = 0; i < data.size(); i++)
		{
			if (data[i] == SOP || data[i] == EOP || data[i] == EscapeCharacter)
			{
				escaped.push_back(EscapeCharacter);
				escaped.push_back(data[i] & 0x0F);
				escaped.push_back(data[i] & 0xF0);
			}
			else
			{
				escaped.push_back(data[i]);
			}
		}

		return escaped;
	}

	DataType::Bytes Parser::Unescape(const DataType::Bytes& data)
	{
		DataType::Bytes unescaped;

		for (DataType::Size i = 0; i < data.size(); i++)
		{
			if (data[i] == EscapeCharacter)
			{
				std::uint8_t c = (data[i + 2]) | (data[i + 1]);
				unescaped.push_back(c);
				i += 2;
			}
			else
			{
				unescaped.push_back(data[i]);
			}
		}

		return unescaped;
	}

	DataType::Bytes Parser::Wrap(const DataType::Bytes& data)
	{
		DataType::Bytes wrapped;
		wrapped.push_back(SOP);
		wrapped.insert(wrapped.end(), data.begin(), data.end());
		wrapped.push_back(EOP);
		return wrapped;
	}

	DataType::Bytes Parser::Unwrap(const DataType::Bytes& data)
	{
		if (data[0] != SOP || data[data.size()-1] != EOP)
		{
			return DataType::Bytes();
		}

		DataType::Bytes unwrapped(data.begin()+1, data.end()-1);
		return unwrapped;
	}

	void Parser::ProcessIncomingData(const DataType::Bytes& data)
	{
		m_Buffer.insert(m_Buffer.end(), data.begin(), data.end());

		int SOPIndex = Find(SOP);

		if (SOPIndex == -1)
		{
			// SOP not found
			m_Buffer.clear();
			return;
		}

		if (SOPIndex > 0)
		{
			m_Buffer.erase(m_Buffer.begin() + (SOPIndex - 1)); // Preserve the SOP
		}

		int EOPIndex = Find(EOP);

		if (EOPIndex > 0)
		{
			DataType::Bytes incoming(m_Buffer.begin(), m_Buffer.begin() + (EOPIndex + 1));
			m_IncomingMessages.push_back(incoming);
			m_Buffer.erase(m_Buffer.begin(), m_Buffer.begin() + EOPIndex);
		}
	}

	DataType::Bytes Parser::GetIncomingMessage()
	{
		if (m_IncomingMessages.empty())
		{
			return DataType::Bytes();
		}

		DataType::Bytes incoming = *m_IncomingMessages.begin();
		m_IncomingMessages.erase(m_IncomingMessages.begin());
		return incoming;
	}

	DataType::Size Parser::Find(DataType::Byte byte)
	{
		for (DataType::Size i = 0; i < m_Buffer.size(); i++)
		{
			if (m_Buffer[i] == byte)
			{
				return i;
			}
		}

		return -1;
	}
}