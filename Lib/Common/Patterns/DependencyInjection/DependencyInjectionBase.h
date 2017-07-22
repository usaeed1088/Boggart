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

	public:
		DependencyInjectionBase(std::string category, std::string moduleName);

		void InjectDependencies(Logger::ILogger* logger) override;
	};
}

#include "DependencyInjectionBase.cpp"