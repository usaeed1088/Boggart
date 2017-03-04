#include "OSAPI.h"

#include "Windows/Windows.h"

namespace Transport
{
	OSAPI* OSAPI::m_Instance = nullptr;

	OSAPI::OSAPI()
	{

	}

	OSAPI::~OSAPI()
	{
		m_Instance = nullptr;
	}

	OSAPI* OSAPI::Instance()
	{
		if (!m_Instance)
		{
			m_Instance = new Windows();
		}

		return m_Instance;
	}
}