#pragma once

#include <Logger/ILogger.h>

#include <string>

namespace Boggart
{
	class IDiagnostics
	{
	public:
		virtual ~IDiagnostics() {}

		virtual void InjectLogger(ILogger* logger) = 0;

		virtual void Log(Logger::Level level, const char* format, ...) = 0;
	};
}