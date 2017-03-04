#include "Physical.h"

namespace Transport
{
	Physical::Physical():
		m_Connected(false)
	{

	}

	Physical::~Physical()
	{
		m_Connected = false;
	}
}