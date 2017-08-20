#include "Subscribable.h"

namespace Boggart
{
	namespace IPC
	{
		Subscribable::Subscribable(std::string subscriberName):
			m_IPC(nullptr),
			m_SubscriberName(subscriberName)
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
			m_IPC->Unsubscribe(shared_from_this());
		}

		std::string Subscribable::Name()
		{
			return m_SubscriberName;
		}
	}
}