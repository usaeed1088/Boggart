#pragma once

#include "IConfiguration.h"

#include <Common/Patterns/DependencyInjection/DependencyInjectionBase.h>

namespace Boggart
{
	template<class T>
	class ConfigurationBase : public IConfiguration, public DependencyInjectionBase<ConfigurationBase<T>>
	{
	public:
		ConfigurationBase();
		virtual ~ConfigurationBase() override;

		bool LoadFromFile(const std::string& path) override;

		virtual T GetParameters() = 0;

	protected:
		bool LoadDefault() override;
		void OnDependenciesInjection() override;

		virtual bool _OnLoadDefault() = 0;
		virtual bool _OnLoadFromFile(const std::string path) = 0;
		virtual void _OnDependenciesInjection() = 0;
	};
}

#include "ConfigurationBase.cpp"