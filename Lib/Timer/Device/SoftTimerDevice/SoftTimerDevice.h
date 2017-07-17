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
			SoftTimerDevice(Id_t id, Span_t span, Type type, Callback_t callback);
			~SoftTimerDevice() override;

		private:
			bool OnStart() override;
			bool OnRestart() override;
			bool OnStop() override;
		};
	}
}