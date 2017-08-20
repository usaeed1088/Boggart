#pragma once

#include "Definition/Definition.h"

#include <memory>
#include <vector>
#include <string>
#include <cstdint>

namespace Boggart
{
	namespace Message
	{
		class IMessage : std::enable_shared_from_this<IMessage>
		{
		public:
			virtual ~IMessage() {}

			virtual std::string Type() = 0;

			virtual std::vector<unsigned char> Encode() = 0;
			virtual bool Decode(const std::vector<unsigned char>& data) = 0;
		};

		typedef std::shared_ptr<IMessage> IMessagePtr;
	}
}