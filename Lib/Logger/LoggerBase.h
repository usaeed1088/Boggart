#pragma once

#include "ILogger.h"

namespace Boggart
{
	class LoggerBase : public ILogger
	{
	public:
		LoggerBase();
		virtual ~LoggerBase() override;

		void Log(Logger::Level level, std::string category, std::string module, const char* format, ...);

	protected:
		virtual void _OnLog(std::string data) = 0;
	};
}