#pragma once

#include "Subscribable/Subscribable.h"

#include "Messages/IPCMessage.h"

#include <string>
#include <memory>
#include <vector>
#include <functional>

namespace Boggart
{
	namespace IPC
	{
		typedef std::function<void(std::string, std::string, std::vector<unsigned char>)> Callback_t;

		class IIPC : public std::enable_shared_from_this<IIPC>
		{
		public:
			virtual ~IIPC() {}

			virtual bool SubscribeMessage(std::shared_ptr<class Subscribable> subscribable, std::string type, Callback_t callback) = 0;
			virtual bool SubscribeSource(std::shared_ptr<class Subscribable> subscribable, std::string type, Callback_t callback) = 0;

			virtual bool UnsubscribeMessage(std::shared_ptr<class Subscribable> subscribable, std::string type) = 0;
			virtual bool UnsubscribeSource(std::shared_ptr<class Subscribable> subscribable, std::string type) = 0;

			virtual bool Unsubscribe(std::shared_ptr<class Subscribable> subscriber) = 0;

			virtual bool Start() = 0;

			virtual bool Send(std::string destination, Message::IMessagePtr message) = 0;
		};

		typedef std::shared_ptr<IIPC> IIPCPtr;
	}
}
