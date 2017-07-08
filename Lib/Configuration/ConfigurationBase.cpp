#include "ConfigurationBase.h"

namespace Boggart
{
	template<class T>
	ConfigurationBase<T>::ConfigurationBase()
	{

	}

	template<class T>
	ConfigurationBase<T>::~ConfigurationBase()
	{

	}

	template<class T>
	bool ConfigurationBase<T>::LoadFromFile(const std::string& path)
	{

	}

	template<class T>
	void ConfigurationBase<T>::OnDependenciesInjection()
	{
		m_Logger->Log()
	}

	template<class T>
	bool ConfigurationBase<T>::LoadDefault()
	{

	}
}