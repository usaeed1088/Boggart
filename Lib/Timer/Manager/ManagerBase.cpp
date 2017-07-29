#include "ManagerBase.h"

namespace Boggart
{
	namespace Timer
	{
		ManagerBase::ManagerBase(std::string moduleName):
			DependencyInjectionBase<ManagerBase>(std::string("Timer"), moduleName),
			m_LastCreatedId(0)
		{

		}

		ManagerBase::~ManagerBase()
		{

		}

		IDevicePtr ManagerBase::Create(Span_t span, _Type type, Callback_t onExpiry)
		{
			m_LastCreatedId++;

			m_Diagnostics.Log(Logger::Level::Debug, "Creating Timer Id %d", m_LastCreatedId);

			return OnCreate(m_LastCreatedId, span, type, onExpiry);
		}

		bool ManagerBase::Destroy(IDevicePtr device)
		{
			m_Diagnostics.Log(Logger::Level::Debug, "Destroying Timer Id %d", device->Id());

			return OnDestroy(device);
		}

		void ManagerBase::Process()
		{
			m_Diagnostics.Log(Logger::Level::Debug, "Processing");

			OnProcess();
		}

		bool ManagerBase::Start(IDevicePtr device)
		{
			m_Diagnostics.Log(Logger::Level::Debug, "Starting Timer Id %d", device->Id());

			return OnStart(device);
		}

		bool ManagerBase::Restart(IDevicePtr device)
		{
			m_Diagnostics.Log(Logger::Level::Debug, "Restarting Timer Id %d", device->Id());

			return OnRestart(device);
		}

		bool ManagerBase::Stop(IDevicePtr device)
		{
			m_Diagnostics.Log(Logger::Level::Debug, "Stopping Timer Id %d", device->Id());

			return OnStop(device);
		}
	}
}