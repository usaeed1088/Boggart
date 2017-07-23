#pragma once

#include <Logger/ILogger.h>
#include <Timer/Manager/IManager.h>

#include <memory>

namespace Boggart
{
	template<class T>
	class IDependencyInjection
	{
	public:
		virtual void InjectDependencies(Logger::ILogger* logger, Timer::IManagerPtr timerManager) = 0;
	};
}