#include "SoftTimerDevice.h"

#include <Lib/Instantiator.h>

namespace Boggart
{
	namespace Timer
	{
		SoftTimerDevice::SoftTimerDevice(Id_t id, Span_t span, Type_t type, Callback_t callback):
			DeviceBase(std::string("SoftTimerDevice"), id, span, type, callback)
		{

		}

		SoftTimerDevice::~SoftTimerDevice()
		{

		}

		void SoftTimerDevice::OnProcess()
		{
			std::uint64_t now = PAL::Instantiator::APIFactory()->GetTimeInstance()->Milliseconds();
			if ((now - m_StartTime) >= Span())
			{
				SetExpired();
			}
		}

		bool SoftTimerDevice::OnStart()
		{
			m_StartTime = PAL::Instantiator::APIFactory()->GetTimeInstance()->Milliseconds();
			return true;
		}

		bool SoftTimerDevice::OnRestart()
		{
			m_StartTime = PAL::Instantiator::APIFactory()->GetTimeInstance()->Milliseconds();
			return true;
		}

		bool SoftTimerDevice::OnStop()
		{
			m_StartTime = 0;
			return true;
		}
	}
}