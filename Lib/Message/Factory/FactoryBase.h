#pragma once

#include "IFactory.h"

namespace Boggart
{
	namespace Message
	{
		class FactoryBase : public IFactory
		{
		protected:
			FactoryBase();

		public:
			virtual ~FactoryBase() override;

			IMessagePtr CreateMessage(const std::vector<unsigned char>& data) override;

		protected:
			virtual IMessagePtr OnCreateMessage(const std::vector<unsigned char>& data) = 0;
		};
	}
}