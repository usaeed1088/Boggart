#include "Generic.h"

#include "../../Utility/Utility.h"

namespace Boggart
{
	namespace Message
	{
		namespace Type
		{
			Generic::Generic(std::string type, std::vector<unsigned char> payload) :
				MessageBase(type),
				m_Payload(payload)
			{

			}

			Generic::Generic(const std::vector<unsigned char>& data) :
				MessageBase(data)
			{
				if (Decode(data))
				{
					m_Valid = true;
				}
			}

			std::vector<unsigned char> Generic::Payload()
			{
				return m_Payload;
			}

			std::vector<unsigned char> Generic::OnEncode()
			{
				std::vector<unsigned char> data;

				Boggart::Message::Utility::EncodeVector(m_Payload, data);

				return data;
			}

			bool Generic::OnDecode(const std::vector<unsigned char>& data)
			{
				if (data.empty())
				{
					return false;
				}

				std::vector<unsigned char> _data = data;

				Boggart::Message::Utility::DecodeVector(m_Payload, _data);

				return true;
			}
		}
	}
}