#include "FactoryBase.h"

namespace Boggart
{
	namespace Message
	{
		FactoryBase::FactoryBase()
		{

		}

		FactoryBase::~FactoryBase()
		{

		}

		IMessagePtr FactoryBase::CreateMessage(const std::vector<unsigned char>& data)
		{
			return OnCreateMessage(data);
		}
	}
}