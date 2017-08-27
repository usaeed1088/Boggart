#include "Ping.h"

namespace Boggart
{
	namespace Transport
	{
		const std::string Ping::s_Type("ping");

		std::string Ping::TypeString()
		{
			return s_Type;
		}

		Ping::Ping():
			Message::MessageBase(s_Type)
		{

		}

		Ping::Ping(const std::vector<unsigned char> data):
			Message::MessageBase(data)
		{
			if (Decode(data))
			{
				m_Valid = true;
			}
		}

		Ping::~Ping()
		{

		}

		std::vector<unsigned char> Ping::OnEncode()
		{
			return std::vector<unsigned char>();
		}

		bool Ping::OnDecode(const std::vector<unsigned char>& data)
		{
			return true;
		}
	}
}