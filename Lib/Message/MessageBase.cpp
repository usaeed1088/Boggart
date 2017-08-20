#include "MessageBase.h"

#include "Utility/Utility.h"

#include <cstdint>

namespace Boggart
{
	namespace Message
	{
		MessageBase::MessageBase(std::string type)
		{

		}

		MessageBase::MessageBase(const std::vector<unsigned char>& data)
		{
			
		}

		MessageBase::~MessageBase()
		{

		}	

		std::vector<unsigned char> MessageBase::Encode()
		{
			return OnEncode();
		}

		bool MessageBase::Decode(const std::vector<unsigned char>& data)
		{
			return OnDecode(data);
		}
	}
}