#pragma once

#include "../DataType.h"

namespace Transport
{
	class Physical
	{
	protected:
		bool m_Connected;

	protected:
		Physical();
		virtual ~Physical();

	public:
		virtual void Send(const DataType::Bytes& data) const = 0;
		virtual DataType::Bytes Receive() const = 0;
	};
}