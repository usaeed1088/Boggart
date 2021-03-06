#include "DiagnosticsBase.h"

#include <Common/Patterns/DependencyInjection/DependencyInjection.h>

namespace Boggart
{
	DiagnosticsBase::DiagnosticsBase(std::string moduleName, std::string category):
		m_ModuleName(moduleName),
		m_Category(category),
		m_Logger(nullptr)
	{

	}

	DiagnosticsBase::~DiagnosticsBase()
	{

	}

	void DiagnosticsBase::InjectLogger(Logger::ILoggerPtr logger)
	{
		m_Logger = logger;
		OnLoggerInjection();
	}

	void DiagnosticsBase::ShareLogger(std::shared_ptr<class DependencyInjection> dependentObject)
	{
		dependentObject->InjectDependency(m_Logger);
	}

	void DiagnosticsBase::Log(Logger::Level level, const char* format, ...)
	{
		// Empty
	}

	void DiagnosticsBase::OnLoggerInjection()
	{
		Log(Logger::Level::Information, "Logger Injected");

		_OnLoggerInjection();
	}

	std::string DiagnosticsBase::ModuleName()
	{
		return m_ModuleName;
	}

	std::string DiagnosticsBase::Category()
	{
		return m_Category;
	}
}