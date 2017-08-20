#pragma once

#include <Lib/Message/Factory/FactoryBase.h>

namespace Boggart
{
	namespace IPC
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