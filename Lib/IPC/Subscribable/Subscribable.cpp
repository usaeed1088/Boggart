#include "Subscribable.h"

namespace Boggart
{
	namespace IPC
	{
		Subscribable::Subscribable():
			m_IPC(nullptr)
		{

		}

		Subscribable::~Subscribable()
		{
			Unsubscribe();
		}

		void Subscribable::InjectIPC(IIPC* ipc)
		{
			m_IPC = ipc;
		}

		void Subscribable::Unsubscribe()
		{
			m_IPC->Unsubscribe(this);
		}
	}
}