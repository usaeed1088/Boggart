#pragma once

#include <Common/Patterns/DependencyInjection/IDependencyInjection.h>

#include "Type.h"
#include "../Common.h"

#include <memory>

namespace Boggart
{
	namespace Timer
	{
		class IDevice : /*public IDependencyInjection<IDevice>,*/ std::enable_shared_from_this<IDevice>
		{
		public:
			virtual ~IDevice() {}

		public:
			virtual void Process() = 0;
			virtual bool Start() = 0;
			virtual bool Restart() = 0;
			virtual bool Stop() = 0;

			virtual Id_t Id() = 0;
			virtual Span_t Span() = 0;
			virtual Type_t Type() = 0;
			virtual Callback_t Callback() = 0;
			virtual bool Running() = 0;
			virtual bool Expired() = 0;
		};

		typedef std::shared_ptr<IDevice> IDevicePtr;
	}
}