#include "MessageBase.h"

#include "Utility/Utility.h"

#include <cstdint>

namespace Boggart
{
	namespace Message
	{
		MessageBase::MessageBase(std::string type):
			m_Type(type)
		{

		}

		MessageBase::MessageBase(const std::vector<unsigned char>& data):
			m_Type()
		{
			
		}

		MessageBase::~MessageBase()
		{

		}	

		std::string MessageBase::Type()
		{
			return m_Type;
		}

		std::vector<unsigned char> MessageBase::Encode()
		{
			std::vector<unsigned char> payload = OnEncode();
			std::vector<unsigned char> data;

			Utility::EncodeString(m_Type, data);	// 0
			Utility::EncodeVector(payload, data);	// 1

			return data;
		}

		bool MessageBase::Decode(const std::vector<unsigned char>& data)
		{
			std::vector<unsigned char> _data = data;
			std::vector<unsigned char> payload;

			Utility::DecodeString(m_Type, _data);	// 0
			Utility::DecodeVector(payload, _data);	// 1

			return OnDecode(payload);
		}
	}
}