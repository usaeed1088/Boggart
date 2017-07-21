#pragma once

#include <memory>
#include <vector>
#include <cstdint>

namespace Boggart
{
	namespace Message
	{
		class IMessage : std::enable_shared_from_this<IMessage>
		{
		public:
			virtual ~IMessage() {}

			virtual bool Valid() = 0;
			virtual std::int16_t Type() = 0;

			virtual std::vector<unsigned char> Encode() = 0;

		protected:
			virtual bool Decode(const std::vector<unsigned char>& data) = 0;
		};

		typedef std::shared_ptr<IMessage> IMessagePtr;
	}
}