#pragma once

#include "IDependencyInjection.h"

#include <Diagnostics/Diagnostics/Diagnsotics.h>

namespace Boggart
{
	template<class T>
	class DependencyInjectionBase : public IDependencyInjection<T>
	{
	protected:
		// Dependencies
		Diagnostics m_Diagnostics;
		Timer::IManagerPtr m_TimerManager;

	public:
		DependencyInjectionBase(std::string category, std::string moduleName);

		void InjectDependencies(Logger::ILogger* logger, Timer::IManagerPtr timerManager) override;
	};
}

#include "DependencyInjectionBase.cpp"