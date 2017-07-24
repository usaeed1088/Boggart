#include "Response.h"

namespace Boggart
{
	namespace IPC
	{
		std::string Response::TypeString()
		{
			return std::string("Response");
		}

		Response::Response(std::string subType):
			MessageBase(TypeString()),
			m_SubType(subType)
		{

		}

		Response::Response(const std::vector<unsigned char>& data):
			MessageBase(data),
			m_SubType()
		{

		}

		Response::~Response()
		{

		}

		std::string Response::SubType()
		{
			return m_SubType;
		}

		std::vector<unsigned char> Response::_OnEncode()
		{
			std::vector<unsigned char> data;

			Message::MessageBase::EncodeString(m_SubType, data);

			return data;
		}

		bool Response::_OnDecode(const std::vector<unsigned char>& data)
		{
			std::vector<unsigned char> _data = data;

			Message::MessageBase::DecodeString(m_SubType, _data);

			return true;
		}
	}
}