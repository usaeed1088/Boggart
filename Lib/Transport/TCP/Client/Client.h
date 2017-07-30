#pragma once

#include "../../TransportBase.h"

#include <string>
#include <cstdint>

namespace Boggart
{
	namespace Transport
	{
		namespace TCP
		{
			class Client : public TransportBase
			{
			private:
				std::string m_ServerIP;
				std::int32_t m_ServerPort;

			public:

			};
		}
	}
}