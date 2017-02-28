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

		void Subscribe(const InProcess* subscriber);
		void Unsubscribe(const InProcess* subscriber);

	public:
		InProcess();
		~InProcess();

		void Send(const Type::Bytes& data) const override;
		Type::Bytes Receive() const override;

	private:
		void Push(const Type::Bytes& data) const;
	};
}