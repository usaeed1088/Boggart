#pragma once

#include <string>

namespace Boggart
{
	namespace IPC
	{
		class ResponseSubtypes
		{
		private:
			ResponseSubtypes();

		public:
			static const std::string Connection;
		};
	}
}