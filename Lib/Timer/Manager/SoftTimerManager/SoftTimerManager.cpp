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

		IDevicePtr SoftTimerManager::OnCreate(Id_t id, Span_t span, Type type, Callback_t onExpiry)
		{
			IDevicePtr device = std::make_shared<SoftTimerDevice>(id, span, type, onExpiry, this);

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
		}

		void SoftTimerManager::OnProcess()
		{
			std::vector<Callback_t> callbacks;

			for (IDevicePtr device : m_Devices)
			{
				if (!device->Running())
				{
					continue;
				}

				// TODO: Need PAL here
				TimePoint_t now = 0;
				std::int32_t elapsed = now - device->StartTime();
				bool expired = elapsed >= device->Span();

				if (!expired)
				{
					continue;
				}

				switch (device->_Type())
				{
				case Type::OneShot:
					break;
				case Type::Periodic:

					break;
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

			(*it)->
		}

		bool SoftTimerManager::OnRestart(IDevicePtr device)
		{
			auto it = Find(device);
			if (it == m_Devices.end())
			{
				return false;
			}
		}

		bool SoftTimerManager::OnStop(IDevicePtr device)
		{
			auto it = Find(device);
			if (it == m_Devices.end())
			{
				return false;
			}
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