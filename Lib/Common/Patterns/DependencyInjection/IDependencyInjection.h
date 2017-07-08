#pragma once

#include <Logger/ILogger.h>

namespace Boggart
{
	template<class T>
	class IDependencyInjection
	{
	public:
		virtual void InjectDependencies(ILogger* logger) = 0;
	};
}