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
		mutable DataType::Queue m_Queue;

		void Subscribe(const InProcess* subscriber);
		void Unsubscribe(const InProcess* subscriber);

	public:
		InProcess();
		~InProcess() override;

		void Send(const DataType::Bytes& data) const override;
		DataType::Bytes Receive() const override;

	private:
		void Process() const override;
		void Push(const DataType::Bytes& data) const;
	};
}