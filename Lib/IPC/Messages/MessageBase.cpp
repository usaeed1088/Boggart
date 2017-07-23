#include "MessageBase.h"

namespace Boggart
{
	namespace IPC
	{
		MessageBase::MessageBase(std::string type):
			Message::MessageBase(type)
		{

		}

		MessageBase::MessageBase(const std::vector<unsigned char>& data):
			Message::MessageBase(data)
		{

		}

		MessageBase::~MessageBase()
		{

		}

		std::vector<unsigned char> MessageBase::OnEncode()
		{
			std::vector<unsigned char> payload = _OnEncode();

			std::vector<unsigned char> data;

			data.insert(data.end(), payload.begin(), payload.end());

			return data;
		}

		bool MessageBase::OnDecode(const std::vector<unsigned char>& data)
		{
			std::vector<unsigned char> _data = data;

			return _OnDecode(_data);
		}
	}
}