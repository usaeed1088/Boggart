#include "SoftTimerManager.h"

#include "../../Device/SoftTimerDevice/SoftTimerDevice.h"

#include <algorithm>

namespace Boggart
{
	namespace Timer
	{
		SoftTimerManager::SoftTimerManager():
			ManagerBase(std::string("SoftTimerManager"))
		{

		}

		SoftTimerManager::~SoftTimerManager()
		{
			for (auto device : m_Devices)
			{
				device->Stop();
			}
		}

		IDevicePtr SoftTimerManager::OnCreate(Id_t id, Span_t span, Type_t type, Callback_t onExpiry)
		{
			std::shared_ptr<SoftTimerDevice> device = std::make_shared<SoftTimerDevice>(id, span, type, onExpiry);

			m_Diagnostics->ShareLogger(std::static_pointer_cast<DependencyInjection>(device));

			m_Devices.push_back(device);

			return device;
		}

		bool SoftTimerManager::OnDestroy(IDevicePtr device)
		{
			auto it = Find(device);
			if (it == m_Devices.end())
			{
				return false;
			}

			m_Devices.erase(it);
			return true;
		}

		void SoftTimerManager::OnProcess()
		{
			std::vector<Callback_t> callbacks;

			for (IDevicePtr device : m_Devices)
			{
				device->Process();

				if (!device->Running())
				{
					continue;
				}

				if (!device->Expired())
				{
					continue;
				}

				switch (device->Type())
				{
				case Type_t::OneShot:
					device->Stop();
					break;
				case Type_t::Periodic:
					device->Restart();
					break;
				}

				callbacks.push_back(device->Callback());
			}

			for (Callback_t callback : callbacks)
			{
				if (callback)
				{
					callback();
				}
			}
		}

		bool SoftTimerManager::OnStart(IDevicePtr device)
		{
			auto it = Find(device);
			if (it == m_Devices.end())
			{
				return false;
			}

			return (*it)->Start();
		}

		bool SoftTimerManager::OnRestart(IDevicePtr device)
		{
			auto it = Find(device);
			if (it == m_Devices.end())
			{
				return false;
			}

			return (*it)->Restart();
		}

		bool SoftTimerManager::OnStop(IDevicePtr device)
		{
			auto it = Find(device);
			if (it == m_Devices.end())
			{
				return false;
			}

			return (*it)->Stop();
		}

		std::vector<IDevicePtr>::iterator SoftTimerManager::Find(IDevicePtr device)
		{
			auto it = std::find_if(m_Devices.begin(), m_Devices.end(), [&device](const IDevicePtr _device)
			{
				return device->Id() == _device->Id();
			});

			return it;
		}
	}
}