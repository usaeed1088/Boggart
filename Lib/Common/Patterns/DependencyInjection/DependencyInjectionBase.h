#pragma once

#include "IDependencyInjection.h"

#include <Diagnostics/IDiagnostics.h>

namespace Boggart
{
	class DependencyInjectionBase : public IDependencyInjection
	{
	protected:
		// Dependencies
		IDiagnosticsPtr m_Diagnostics;
		Timer::IManagerPtr m_TimerManager;

	public:
		DependencyInjectionBase(std::string category, std::string moduleName);

		void InjectDependencies(Logger::ILoggerPtr logger) override;
		void InjectDependencies(Logger::ILoggerPtr logger, Timer::IManagerPtr timerManager) override;
	};
}