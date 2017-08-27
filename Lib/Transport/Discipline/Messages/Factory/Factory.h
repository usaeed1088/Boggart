#pragma once

#include <Message/Factory/FactoryBase.h>

namespace Boggart
{
	namespace Transport
	{
		class Factory : public Message::FactoryBase
		{
		public:
			Factory();
			~Factory() override;

		private:
			Message::IMessagePtr OnCreateMessage(const std::vector<unsigned char>& data) override;
		};
	}
}