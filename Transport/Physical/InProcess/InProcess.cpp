#include "InProcess.h"

#include <algorithm>

namespace Transport
{
	std::vector<const InProcess*> InProcess::Subscribers;

	InProcess::InProcess()
	{
		m_Connected = true;
	}

	void InProcess::Subscribe(const InProcess* subscriber)
	{
		std::vector<const InProcess*>::const_iterator it = std::find(Subscribers.begin(), Subscribers.end(), subscriber);

		if (it == Subscribers.end()) // Not found ?
		{
			Subscribers.push_back(subscriber);
		}
	}

	void InProcess::Unsubscribe(const InProcess* subscriber)
	{
		std::vector<const InProcess*>::const_iterator it = std::find(Subscribers.begin(), Subscribers.end(), subscriber);

		if (it != Subscribers.end()) // Found ?
		{
			Subscribers.erase(it);
		}
	}

	void InProcess::Send(const Type::Bytes& data) const
	{
		for (const InProcess* subscriber : Subscribers)
		{
			if (subscriber == this) { continue; }
			subscriber->Push(data);
		}
	}

	Type::Bytes InProcess::Receive() const
	{
		std::lock_guard<std::mutex> lock(m_QueueLock);

		if (m_Queue.empty()) { return Type::Bytes(); }

		Type::Bytes data = m_Queue.back();
		m_Queue.erase(m_Queue.begin());
		return data;
	}

	void InProcess::Push(const Type::Bytes& data) const
	{
		std::lock_guard<std::mutex> lock(m_QueueLock);
		m_Queue.push_back(data);
	}
}