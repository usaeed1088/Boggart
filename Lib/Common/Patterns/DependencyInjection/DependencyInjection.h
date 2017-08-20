#pragma once

#include <Lib/Logger/ILogger.h>
#include <Lib/Transport/ITransport.h>
#include <Lib/Timer/Manager/IManager.h>
#include <Lib/Diagnostics/IDiagnostics.h>

#include <memory>
#include <string>

namespace Boggart
{
	namespace Timer { class IManager; }
	namespace Transport { class ITransport; }

	class DependencyInjection
	{
	protected:
		// Dependencies
		std::shared_ptr<IDiagnostics> m_Diagnostics;
		std::shared_ptr<Timer::IManager> m_TimerManager;
		std::shared_ptr<Transport::ITransport> m_Transport;

	public:
		DependencyInjection(std::string category, std::string moduleName);

		void InjectDependency(std::shared_ptr<Logger::ILogger> logger);
		void InjectDependency(std::shared_ptr<Timer::IManager> timerManager);
		void InjectDependency(std::shared_ptr<Transport::ITransport> transport);
	};
}