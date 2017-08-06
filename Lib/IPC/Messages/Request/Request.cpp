#include "Request.h"

#include <Lib/Message/Utility/Utility.h>

namespace Boggart
{
	namespace IPC
	{
		std::string Request::TypeString()
		{
			return std::string("Request");
		}

		Request::Request(std::string subType):
			MessageBase(TypeString()),
			m_SubType(subType)
		{

		}

		Request::Request(const std::vector<unsigned char>& data):
			MessageBase(data),
			m_SubType()
		{

		}

		Request::~Request()
		{

		}

		std::string Request::SubType()
		{
			return m_SubType;
		}

		std::vector<unsigned char> Request::_OnEncode()
		{
			std::vector<unsigned char> data;

			Message::Utility::EncodeString(m_SubType, data);

			return data;
		}

		bool Request::_OnDecode(const std::vector<unsigned char>& data)
		{
			std::vector<unsigned char> _data = data;

			Message::Utility::DecodeString(m_SubType, _data);

			return true;
		}
	}
}