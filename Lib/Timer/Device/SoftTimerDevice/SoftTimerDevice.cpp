#include "SoftTimerDevice.h"

namespace Boggart
{
	namespace Timer
	{
		SoftTimerDevice::SoftTimerDevice(Id_t id, Span_t span, Type type, Callback_t callback):
			DeviceBase(std::string("SoftTimerDevice"), id, span, type, callback)
		{

		}

		SoftTimerDevice::~SoftTimerDevice()
		{

		}

		bool SoftTimerDevice::OnStart()
		{
			// TODO: Update Start Time
		}

		bool SoftTimerDevice::OnRestart()
		{

		}

		bool SoftTimerDevice::OnStop()
		{

		}
	}
}