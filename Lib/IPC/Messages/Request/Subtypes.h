#pragma once

#include <string>

namespace Boggart
{
	namespace IPC
	{
		class RequestSubtypes
		{
		private:
			RequestSubtypes();

		public:
			static const std::string KeepAlive;
		};
	}
}