#pragma once

#include "IIPC.h"

#include <Lib/Transport/ITransport.h>
#include <Lib/Common/Patterns/DependencyInjection/DependencyInjectionBase.h>

#include "Messages/Factory/Factory.h"
#include "ConnectionManager/ConnectionManager.h"

#include <map>
#include <string>
#include <vector>

namespace Boggart
{
	namespace IPC
	{
		class IPCBase : public IIPC, public DependencyInjectionBase
		{
		private:
			typedef std::string SubscriberName;
			typedef std::string Type;
			typedef std::string TableName;

			typedef std::map<SubscriberName, Callback_t> Subscriber;
			typedef std::map<Type, Subscriber> Subscription;
			typedef std::map<TableName, Subscription> SubscriptionTable;

			SubscriptionTable m_SubscriptionTable;

			Transport::ITransportPtr m_Transport;

			std::shared_ptr<ConnectionManager> m_ConnectionManager;

		protected:
			Factory m_Factory;

		private:
			std::string m_MyId;

		protected:
			IPCBase(std::string moduleName, std::string myId);

		public:
			virtual ~IPCBase() override;

			void InjectTransport(Transport::ITransportPtr transport);

			bool SubscribeMessage(SubscribablePtr subscriber, std::string type, Callback_t callback) override;
			bool SubscribeSource(SubscribablePtr subscriber, std::string type, Callback_t callback) override;

			bool UnsubscribeMessage(SubscribablePtr subscriber, std::string type) override;
			bool UnsubscribeSource(SubscribablePtr subscriber, std::string type) override;

			bool Unsubscribe(SubscribablePtr subscriber) override;

			bool Start() override;

			bool Send(std::string destination, Message::IMessagePtr message) override;

		private:
			bool Subscribe(std::string table, SubscribablePtr subscriber, std::string type, Callback_t callback);
			bool Unsubscribe(std::string table, SubscribablePtr subscriber, std::string type);

			std::uint8_t GenerateSequenceNumber();

		protected:
			void SendToTransport(std::vector<unsigned char> data);
			std::vector<unsigned char> ReceiveFromTransport();

			void OnReceive(Message::IMessagePtr message);

		protected:
			virtual bool OnStart() = 0;
			virtual bool OnSend(Message::IMessagePtr message) = 0;
		};
	}
}