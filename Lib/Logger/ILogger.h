#pragma once

#include "Level.h"

#include <string>

namespace Boggart
{
	namespace Logger
	{
		class ILogger
		{
		public:
			virtual ~ILogger() {}

			virtual void Log(Logger::Level level, std::string category, std::string module, const char* format, ...) = 0;
		};
	}
}