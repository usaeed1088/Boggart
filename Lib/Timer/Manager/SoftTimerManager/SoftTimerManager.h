#pragma once

#include "../ManagerBase.h"

#include <vector>

namespace Boggart
{
	namespace Timer
	{
		class SoftTimerManager : public ManagerBase
		{
		private:
			std::vector<IDevicePtr> m_Devices;

		public:
			SoftTimerManager();
			~SoftTimerManager() override;

		private:
			IDevicePtr OnCreate(Id_t id, Span_t span, Type_t type, Callback_t onExpiry) override;
			bool OnDestroy(IDevicePtr device) override;

			void OnProcess() override;

			bool OnStart(IDevicePtr device) override;
			bool OnRestart(IDevicePtr device) override;
			bool OnStop(IDevicePtr device) override;

		private:
			inline std::vector<IDevicePtr>::iterator Find(IDevicePtr device);
		};
	}
}