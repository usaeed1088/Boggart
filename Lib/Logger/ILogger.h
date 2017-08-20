#pragma once

#include "Level.h"

#include <string>
#include <memory>

namespace Boggart
{
	namespace Logger
	{
		class ILogger
		{
		public:
			virtual ~ILogger() {}

			virtual void EnableLevel(Logger::Level level) = 0;

			virtual void EnableCategory(std::string category) = 0;

			virtual void EnableModule(std::string module) = 0;

			virtual void Log(Logger::Level level, std::string category, std::string module, const char* format, ...) = 0;
		};

		typedef std::shared_ptr<ILogger> ILoggerPtr;
	}
}