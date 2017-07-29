#pragma once

#include <Logger/ILogger.h>
#include <Common/Patterns/DependencyInjection/IDependencyInjection.h>

#include <string>

namespace Boggart
{
	class IDiagnostics
	{
	public:
		virtual ~IDiagnostics() {}

		virtual void InjectLogger(Logger::ILoggerPtr logger) = 0;

		virtual void Log(Logger::Level level, const char* format, ...) = 0;
	};
}