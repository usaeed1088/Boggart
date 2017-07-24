#pragma once

#include "IDevice.h"

#include <Common/Patterns/DependencyInjection/DependencyInjectionBase.h>

#include "../Manager/IManager.h"

#include <string>

namespace Boggart
{
	namespace Timer
	{
		class DeviceBase : public IDevice, public DependencyInjectionBase<DeviceBase>
		{
		private:
			Id_t m_Id;
			Span_t m_Span;
			_Type m_Type;
			Callback_t m_OnExpiry;
			bool m_Running;
			bool m_Expired;

		protected:
			DeviceBase(std::string moduleName, Id_t id, Span_t span, _Type type, Callback_t onExpiry);

		public:
			virtual ~DeviceBase() override;

			void Process() override;
			bool Start() override;
			bool Restart() override;
			bool Stop() override;

			Id_t Id() override;
			Span_t Span() override;
			Type_t Type() override;
			Callback_t Callback() override;
			bool Running() override;
			bool Expired() override;

		protected:
			virtual void OnProcess() = 0;
			virtual bool OnStart() = 0;
			virtual bool OnRestart() = 0;
			virtual bool OnStop() = 0;

		protected:
			void SetExpired();
		};
	}
}