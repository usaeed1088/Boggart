#pragma once

#include "../Common.h"
#include "../Device/IDevice.h"

#include <memory>

namespace Boggart
{
	namespace Timer
	{
		class IManager : public std::enable_shared_from_this<IManager>
		{
		public:
			virtual ~IManager() {}

		public:
			virtual IDevicePtr Create(Span_t span, _Type type, Callback_t onExpiry) = 0;
			virtual bool Destroy(IDevicePtr device) = 0;

			virtual void Process() = 0;

			virtual bool Start(IDevicePtr device) = 0;
			virtual bool Restart(IDevicePtr device) = 0;
			virtual bool Stop(IDevicePtr device) = 0;
		};

		typedef std::shared_ptr<IManager> IManagerPtr;
	}
}