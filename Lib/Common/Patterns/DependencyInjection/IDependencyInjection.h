#pragma once

#include <Logger/ILogger.h>
#include <Timer/Manager/IManager.h>

#include <memory>

namespace Boggart
{
	class IDependencyInjection : std::enable_shared_from_this<IDependencyInjection>
	{
	public:
		virtual void InjectDependencies(Logger::ILoggerPtr logger) = 0;
		virtual void InjectDependencies(Logger::ILoggerPtr logger, Timer::IManagerPtr timerManager) = 0;
	};

	typedef std::shared_ptr<IDependencyInjection> IDependencyInjectionPtr;
}