#pragma once

#include <memory>

namespace Boggart
{
	namespace Transport
	{
		class IDiscipline : std::enable_shared_from_this<IDiscipline>
		{
		public:
			virtual ~IDiscipline() {}
		};
	}
}