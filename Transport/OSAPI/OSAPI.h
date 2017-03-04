#pragma once

#include "SocketAPI.h"

namespace Transport
{
	class OSAPI : public SocketAPI
	{
	private:
		static OSAPI* m_Instance;

	protected:
		OSAPI();
		virtual ~OSAPI();

	public:
		static OSAPI* Instance();
	};
}