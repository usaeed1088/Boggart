#include "Factory.h"

#include <Lib/Message/Utility/Utility.h>

#include "../Request/Request.h"
#include "../Response/Response.h"

namespace Boggart
{
	namespace IPC
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

			if (type == Request::TypeString())
			{
				message = std::shared_ptr<Request>(new Request(data));
			}
			else if (type == Response::TypeString())
			{
				message = std::shared_ptr<Response>(new Response(data));
			}

			if (message && !message->Decode(data))
			{
				message = nullptr;
			}

			return message;
		}
	}
}