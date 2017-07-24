#include "Diagnsotics.h"

#include <cstdarg>

namespace Boggart
{
	Diagnostics::Diagnostics(std::string moduleName, std::string category):
		DiagnosticsBase(moduleName, category)
	{

	}

	Diagnostics::~Diagnostics()
	{

	}

	void Diagnostics::Log(Logger::Level level, const char* format, ...)
	{
		char buffer[1024] = {};

		va_list args;
		va_start(args, format);
		vsnprintf(buffer, sizeof(buffer), format, args);
		va_end(args);

		m_Logger->Log(level, Category(), ModuleName(), buffer);
	}

	void Diagnostics::_OnLoggerInjection()
	{
		// Empty
	}
}