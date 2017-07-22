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

		public:
			Subscribable();
			~Subscribable();

		private:
			friend class IPCBase;
			void InjectIPC(class IIPC* ipc);
			void Unsubscribe();
		};

		typedef class Subscribable* SubscribablePtr;
	}
}