#pragma once

#include <memory>
#include <vector>
#include <string>

namespace Boggart
{
	namespace Event
	{
		class IEvent : std::enable_shared_from_this<IEvent>
		{
		public:
			virtual ~IEvent() {}

			virtual std::string Type() = 0;

			virtual std::vector<unsigned char> Encode() = 0;

		protected:
			virtual bool Decode(const std::vector<unsigned char>& data) = 0;
		};

		typedef std::shared_ptr<IEvent> IEventPtr;
	}
}