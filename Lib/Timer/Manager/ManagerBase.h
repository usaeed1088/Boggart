#pragma once

#include "IManager.h"

#include <Common/Patterns/DependencyInjection/DependencyInjectionBase.h>

#include <string>

namespace Boggart
{
	namespace Timer
	{
		class ManagerBase : public IManager, public DependencyInjectionBase<ManagerBase>
		{
		private:
			Id_t m_LastCreatedId;

		protected:
			ManagerBase(std::string moduleName);

		public:
			virtual ~ManagerBase() override;

			IDevicePtr Create(Span_t span, _Type type, Callback_t callback) override;
			bool Destroy(IDevicePtr device) override;

			void Process() override;

			bool Start(IDevicePtr device) override;
			bool Restart(IDevicePtr device) override;
			bool Stop(IDevicePtr device) override;

		protected:
			virtual IDevicePtr OnCreate(Id_t id, Span_t span, _Type type, Callback_t onExpiry) = 0;
			virtual bool OnDestroy(IDevicePtr device) = 0;

		protected:
			virtual void OnProcess() = 0;
			virtual bool OnStart(IDevicePtr device) = 0;
			virtual bool OnRestart(IDevicePtr device) = 0;
			virtual bool OnStop(IDevicePtr device) = 0;
		};
	}
}