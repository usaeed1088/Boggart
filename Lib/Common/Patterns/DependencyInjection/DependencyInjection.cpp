#include "DependencyInjection.h"

#include <Diagnostics/Diagnostics/Diagnsotics.h>

namespace Boggart
{
	DependencyInjection::DependencyInjection(std::string category, std::string moduleName):
		m_Diagnostics(new Diagnostics(moduleName, category)),
		m_TimerManager(nullptr),
		m_Transport(nullptr)
	{

	}

	void DependencyInjection::InjectDependencies(std::shared_ptr<Logger::ILogger> logger)
	{
		m_Diagnostics->InjectLogger(logger);
	}

	void DependencyInjection::InjectDependencies(std::shared_ptr<Timer::IManager> timerManager)
	{
		m_TimerManager = timerManager;
	}

	void DependencyInjection::InjectDependencies(std::shared_ptr<Transport::ITransport> transport)
	{
		m_Transport = transport;
	}
}