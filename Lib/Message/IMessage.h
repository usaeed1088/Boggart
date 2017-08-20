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

			virtual bool Valid() = 0;
			virtual std::string Type() = 0;

			virtual void Source(std::string source) = 0;
			virtual void Destination(std::string destination) = 0;

			virtual std::string Source() = 0;
			virtual std::string Destination() = 0;

			virtual void SequenceNumber(std::uint8_t sequenceNumber) = 0;
			virtual std::uint8_t SequenceNumber() = 0;

			virtual std::vector<unsigned char> Encode() = 0;
			virtual bool Decode(const std::vector<unsigned char>& data) = 0;
		};

		typedef std::shared_ptr<IMessage> IMessagePtr;
	}
}