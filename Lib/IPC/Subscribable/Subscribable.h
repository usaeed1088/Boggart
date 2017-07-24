#pragma once

#include "../IIPC.h"

#include <string>
#include <memory>

namespace Boggart
{
	namespace IPC
	{
		class Subscribable
		{
		private:
			class IIPC* m_IPC;
			std::string m_SubscriberName;

		public:
			Subscribable(std::string subscriberName);
			~Subscribable();

		private:
			friend class IPCBase;
			void InjectIPC(class IIPC* ipc);
			void Unsubscribe();
			std::string Name();
		};

		typedef class Subscribable* SubscribablePtr;
	}
}