#pragma once

#include "IDependencyInjection.h"

#include <Diagnostics/Diagnostics/Diagnsotics.h>

namespace Boggart
{
	// TODO: May be tamplate is not needed here ?
	template<class T>
	class DependencyInjectionBase : public IDependencyInjection
	{
	protected:
		// Dependencies
		class Diagnostics m_Diagnostics;
		Timer::IManagerPtr m_TimerManager;

	public:
		DependencyInjectionBase(std::string category, std::string moduleName);

		void InjectDependencies(Logger::ILoggerPtr logger) override;
		void InjectDependencies(Logger::ILoggerPtr logger, Timer::IManagerPtr timerManager) override;
	};
}

#include "DependencyInjectionBase.cpp"