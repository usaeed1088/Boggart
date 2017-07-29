#include "DeviceBase.h"

namespace Boggart
{
	namespace Timer
	{
		DeviceBase::DeviceBase(std::string moduleName, Id_t id, Span_t span, _Type type, Callback_t onExpiry):
			DependencyInjectionBase(std::string("Timer"), moduleName),
			m_Id(id),
			m_Span(span),
			m_Type(type),
			m_OnExpiry(onExpiry),
			m_Running(false),
			m_Expired(false)
		{

		}

		DeviceBase::~DeviceBase()
		{

		}

		void DeviceBase::Process()
		{
			OnProcess();
		}

		bool DeviceBase::Start()
		{
			m_Diagnostics->Log(Logger::Level::Debug, "Starting Timer Id %d", m_Id);
			m_Running = true;
			m_Expired = false;
			return OnStart();
		}

		bool DeviceBase::Restart()
		{
			m_Diagnostics->Log(Logger::Level::Debug, "Restarting Timer Id %d", m_Id);
			m_Running = true;
			m_Expired = false;
			return OnRestart();
		}

		bool DeviceBase::Stop()
		{
			m_Diagnostics->Log(Logger::Level::Debug, "Stopping Timer Id %d", m_Id);
			m_Running = false;
			m_Expired = false;
			return OnStop();
		}

		Id_t DeviceBase::Id()
		{
			return m_Id;
		}

		Span_t DeviceBase::Span()
		{
			return m_Span;
		}

		_Type DeviceBase::Type()
		{
			return m_Type;
		}

		Callback_t DeviceBase::Callback()
		{
			return m_OnExpiry;
		}

		bool DeviceBase::Running()
		{
			return m_Running;
		}

		bool DeviceBase::Expired()
		{
			return m_Expired;
		}

		void DeviceBase::SetExpired()
		{
			m_Expired = true;
		}
	}
}