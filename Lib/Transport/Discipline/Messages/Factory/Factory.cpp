#include "Factory.h"

#include <Message/Utility/Utility.h>

#include "../Ping/Ping.h"
#include "../Pong/Pong.h"

namespace Boggart
{
	namespace Transport
	{
		Factory::Factory()
		{

		}

		Factory::~Factory()
		{

		}

		Message::IMessagePtr Factory::OnCreateMessage(const std::vector<unsigned char>& data)
		{
			Message::IMessagePtr message;
			// TODO: Find a better way to determine type of incoming message
			// At this stage, any change in message header must be reflected here
			std::vector<unsigned char> _data = data;
			std::string type;
			Message::Utility::DecodeString(type, _data);

			if (type == Ping::TypeString())
			{
				message = std::shared_ptr<Ping>(new Ping(data));
			}
			else if (type == Pong::TypeString())
			{
				message = std::shared_ptr<Pong>(new Pong(data));
			}

			if (message && !message->Decode(data))
			{
				message = nullptr;
			}

			if (!message->Valid())
			{
				message = nullptr;
			}

			return message;
		}
	}
}