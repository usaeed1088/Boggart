#include "LoggerBase.h"

#include <sstream>
#include <cstdarg>

namespace Boggart
{
	namespace Logger
	{
		LoggerBase::LoggerBase()
		{

		}

		LoggerBase::~LoggerBase()
		{

		}

		void LoggerBase::Log(Logger::Level level, std::string category, std::string module, const char* format, ...)
		{
			// Format
			char buffer[1024] = {};

			va_list args;
			va_start(args, format);
			vsnprintf(buffer, sizeof(buffer), format, args);
			va_end(args);

			std::stringstream ss;

			ss << "[" << "timestamp_placeholder" << "] ";
			ss << "[" << level << "] ";
			ss << "[" << category << "] ";
			ss << "[" << module << "] ";
			ss << "[" << std::string(buffer) << "]";

			// Log
			_OnLog(ss.str());
		}
	}
}