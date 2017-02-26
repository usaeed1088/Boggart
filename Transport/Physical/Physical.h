#pragma once

#include "../Type.h"

namespace Transport
{
	class Physical
	{
	protected:
		bool m_Connected;

	protected:
		Physical();

	public:
		virtual void Send(const Type::Bytes& data) const = 0;
		virtual Type::Bytes Receive() const = 0;
	};
}