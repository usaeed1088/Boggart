#include "DependencyInjectionBase.h"

#include <Diagnostics/Diagnostics/Diagnsotics.h>

namespace Boggart
{
	DependencyInjectionBase::DependencyInjectionBase(std::string category, std::string moduleName):
		m_Diagnostics(new Diagnostics(moduleName, category)),
		m_TimerManager(nullptr)
	{

	}

	void DependencyInjectionBase::InjectDependencies(Logger::ILoggerPtr logger)
	{
		m_Diagnostics->InjectLogger(logger);
	}

	void DependencyInjectionBase::InjectDependencies(Timer::IManagerPtr timerManager)
	{
		m_TimerManager = timerManager;
	}

	void DependencyInjectionBase::InjectDependencies(Logger::ILoggerPtr logger, Timer::IManagerPtr timerManager)
	{
		m_Diagnostics->InjectLogger(logger);
		m_TimerManager = timerManager;
	}
}