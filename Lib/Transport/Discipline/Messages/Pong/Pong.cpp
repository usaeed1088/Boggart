#include "Pong.h"

namespace Boggart
{
	namespace Transport
	{
		const std::string Pong::s_Type("pong");

		std::string Pong::TypeString()
		{
			return s_Type;
		}

		Pong::Pong() :
			Message::MessageBase(s_Type)
		{

		}

		Pong::Pong(const std::vector<unsigned char> data) :
			Message::MessageBase(data)
		{
			if (Decode(data))
			{
				m_Valid = true;
			}
		}

		Pong::~Pong()
		{

		}

		std::vector<unsigned char> Pong::OnEncode()
		{
			return std::vector<unsigned char>();
		}

		bool Pong::OnDecode(const std::vector<unsigned char>& data)
		{
			return true;
		}
	}
}