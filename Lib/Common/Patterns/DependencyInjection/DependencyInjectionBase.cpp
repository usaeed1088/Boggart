#include "DependencyInjectionBase.h"

namespace Boggart
{
	template<class T>
	DependencyInjectionBase<T>::DependencyInjectionBase(std::string category, std::string moduleName):
		m_Diagnostics(moduleName, category),
		m_TimerManager(nullptr)
	{

	}

	template<class T>
	void DependencyInjectionBase<T>::InjectDependencies(Logger::ILogger* logger, Timer::IManagerPtr timerManager)
	{
		m_Diagnostics.InjectLogger(logger);
		m_TimerManager = timerManager;
	}
}