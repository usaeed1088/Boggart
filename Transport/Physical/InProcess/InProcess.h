#pragma once

#include "../Physical.h"

#include <mutex>

namespace Transport
{
	class InProcess : public Physical
	{
	private:
		static std::vector<const InProcess*> Subscribers;

	private:
		mutable std::mutex m_QueueLock;
		mutable Type::Queue m_Queue;

	public:
		InProcess();

		static void Subscribe(const InProcess* subscriber);
		static void Unsubscribe(const InProcess* subscriber);

		void Send(const Type::Bytes& data) const override;
		Type::Bytes Receive() const override;

	private:
		void Push(const Type::Bytes& data) const;
	};
}