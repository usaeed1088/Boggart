#pragma once

#include "IIPC.h"

#include "../Transport/ITransport.h"
#include "../Common/Patterns/DependencyInjection/DependencyInjectionBase.h"

#include <map>
#include <string>
#include <vector>

namespace Boggart
{
	namespace IPC
	{
		class IPCBase : public IIPC, DependencyInjectionBase<IPCBase>
		{
		private:
			typedef std::map<std::string, Callback_t> Subscription;
			typedef std::map<SubscribablePtr, Subscription> Subscriber;
			typedef std::map<std::string, Subscriber> SubscriptionTable;

			SubscriptionTable m_SubscriptionTable;

			Transport::ITransportPtr m_Transport;

		private:
			std::string m_MyId;

		protected:
			IPCBase(std::string moduleName, std::string myId);

		public:
			virtual ~IPCBase() override;

			void InjectTransport(Transport::ITransportPtr transport);

			bool SubscribeEvent(SubscribablePtr subscriber, std::string type, Callback_t callback) override;
			bool SubscribeMessage(SubscribablePtr subscriber, std::string type, Callback_t callback) override;
			bool SubscribeSource(SubscribablePtr subscriber, std::string type, Callback_t callback) override;

			bool UnsubscribeEvent(SubscribablePtr subscriber, std::string type) override;
			bool UnsubscribeMessage(SubscribablePtr subscriber, std::string type) override;
			bool UnsubscribeSource(SubscribablePtr subscriber, std::string type) override;

			bool Unsubscribe(SubscribablePtr subscriber) override;

			bool Send(std::string destination, Message::IMessagePtr message) override;

		private:
			bool Subscribe(std::string table, SubscribablePtr subscriber, std::string type, Callback_t callback);
			bool Unsubscribe(std::string table, SubscribablePtr subscriber, std::string type);

			std::uint8_t GenerateSequenceNumber();

		protected:
			virtual bool OnSubscribeEvent(SubscribablePtr subscriber, std::string type, Callback_t callback) = 0;
			virtual bool OnSubscribeMessage(SubscribablePtr subscriber, std::string type, Callback_t callback) = 0;
			virtual bool OnSubscribeSource(SubscribablePtr subscriber, std::string type, Callback_t callback) = 0;

			virtual bool OnUnsubscribeEvent(SubscribablePtr subscriber, std::string type) = 0;
			virtual bool OnUnsubscribeMessage(SubscribablePtr subscriber, std::string type) = 0;
			virtual bool OnUnsubscribeSource(SubscribablePtr subscriber, std::string type) = 0;

			virtual bool OnSend(std::string destination, Message::IMessagePtr message) = 0;
		};
	}
}