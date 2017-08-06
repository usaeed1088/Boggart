#pragma once

#include "../IMessage.h"

#include <memory>
#include <vector>

namespace Boggart
{
	namespace Message
	{
		class IFactory : public std::enable_shared_from_this<IFactory>
		{
		public:
			virtual ~IFactory() {}

			virtual IMessagePtr CreateMessage(const std::vector<unsigned char>& data) = 0;
		};
	}
}