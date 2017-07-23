#pragma once

#include "Subscribable/Subscribable.h"

#include "../Message/IMessage.h"

#include <string>
#include <memory>
#include <vector>
#include <functional>

namespace Boggart
{
	namespace IPC
	{
		typedef std::function<void(Message::IMessagePtr)> Callback_t;

		class IIPC : std::enable_shared_from_this<IIPC>
		{
		public:
			virtual ~IIPC() {}

			virtual bool SubscribeMessage(class Subscribable* subscribable, std::string type, Callback_t callback) = 0;
			virtual bool SubscribeSource(class Subscribable* subscribable, std::string type, Callback_t callback) = 0;

			virtual bool UnsubscribeMessage(class Subscribable* subscribable, std::string type) = 0;
			virtual bool UnsubscribeSource(class Subscribable* subscribable, std::string type) = 0;

			virtual bool Unsubscribe(class Subscribable* subscriber) = 0;

			virtual bool Start() = 0;

			virtual bool Send(std::string destination, Message::IMessagePtr message) = 0;
		};

		typedef std::shared_ptr<IIPC> IIPCPtr;
	}
}