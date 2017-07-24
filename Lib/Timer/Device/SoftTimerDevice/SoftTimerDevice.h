#pragma once

#include "../DeviceBase.h"

namespace Boggart
{
	namespace Timer
	{
		class SoftTimerDevice : public DeviceBase
		{
		private:
			TimePoint_t m_StartTime;

		public:
			SoftTimerDevice(Id_t id, Span_t span, Type_t type, Callback_t callback);
			~SoftTimerDevice() override;

		private:
			void OnProcess() override;
			bool OnStart() override;
			bool OnRestart() override;
			bool OnStop() override;
		};
	}
}