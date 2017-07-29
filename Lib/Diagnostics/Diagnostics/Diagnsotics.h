#pragma once

#include <Common/Patterns/DependencyInjection/DependencyInjectionBase.h>

#include "../DiagnosticsBase.h"

namespace Boggart
{
	class Diagnostics : public DiagnosticsBase
	{
	public:
		Diagnostics(std::string moduleName, std::string category);
		~Diagnostics() override;

		void ShareLogger(std::shared_ptr<class IDependencyInjection> dependentObject);
		void Log(Logger::Level level, const char* format, ...) override;

	private:
		void _OnLoggerInjection();
	};
}