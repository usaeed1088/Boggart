#include "IPCBase.h"

namespace Boggart
{
	namespace IPC
	{
		const std::string MESSAGE_TABLE("MESSAGES");
		const std::string SOURCE_TABLE("SOURCES");

		IPCBase::IPCBase(std::string moduleName, std::string myId):
			DependencyInjection(std::string("IPC"), moduleName),
			m_SubscriptionTable(),
			m_ConnectionManager(new ConnectionManager(myId, std::bind(&IPCBase::Send, this, std::placeholders::_1, std::placeholders::_2))),
			m_MyId(myId)
		{

		}

		IPCBase::~IPCBase()
		{

		}

		bool IPCBase::SubscribeMessage(SubscribablePtr subscriber, std::string type, Callback_t callback)
		{
			return Subscribe(MESSAGE_TABLE, subscriber, type, callback);
		}

		bool IPCBase::SubscribeSource(SubscribablePtr subscriber, std::string type, Callback_t callback)
		{
			return Subscribe(SOURCE_TABLE, subscriber, type, callback);
		}

		bool IPCBase::UnsubscribeMessage(SubscribablePtr subscriber, std::string type)
		{
			return Unsubscribe(MESSAGE_TABLE, subscriber, type);
		}

		bool IPCBase::UnsubscribeSource(SubscribablePtr subscriber, std::string type)
		{
			return Unsubscribe(SOURCE_TABLE, subscriber, type);
		}

		bool IPCBase::Unsubscribe(SubscribablePtr subscriber)
		{
			// Iterate over tables
			for (SubscriptionTable::iterator it = m_SubscriptionTable.begin(); it != m_SubscriptionTable.end(); ++it)
			{
				// Iterate over event/message types
				for (Subscription::iterator iit = it->second.begin(); iit != it->second.end(); ++iit)
				{
					// Check if there is a subscriber on this type
					if (iit->second.find(subscriber->Name()) != iit->second.end())
					{
						// Erase that subscriber
						iit->second.erase(subscriber->Name());
					}
				}
			}

			m_Diagnostics->Log(Logger::Level::Information, "%s Unsubscribed", subscriber->Name().c_str());

			return true;
		}

		bool IPCBase::Start()
		{
			m_Diagnostics->Log(Logger::Level::Information, "Starting");

			m_Diagnostics->ShareLogger(m_ConnectionManager);
			m_ConnectionManager->InjectDependency(m_TimerManager);

			Subscribe(MESSAGE_TABLE, m_ConnectionManager, Request::TypeString(), std::bind(&ConnectionManager::OnIncomingMessage, m_ConnectionManager, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
			Subscribe(MESSAGE_TABLE, m_ConnectionManager, Response::TypeString(), std::bind(&ConnectionManager::OnIncomingMessage, m_ConnectionManager, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

			//m_ConnectionManager->Start();

			return OnStart();
		}

		bool IPCBase::Send(std::string destination, Message::IMessagePtr message)
		{
			IPCMessagePtr ipcMessage(new IPCMessage(message->Type()));

			ipcMessage->SequenceNumber(GenerateSequenceNumber());
			ipcMessage->Destination(destination);
			ipcMessage->Source(m_MyId);
			ipcMessage->ApplicationPayload(message->Encode());

			m_Diagnostics->Log(Logger::Level::Debug, "Sending Message Sequence Number [%d] to [%s]", (std::int32_t)ipcMessage->SequenceNumber(), destination.c_str());

			// TODO: Handle Retransmissions here?

			return OnSend(ipcMessage);
		}

		bool IPCBase::Subscribe(std::string table, SubscribablePtr subscriber, std::string type, Callback_t callback)
		{
			subscriber->InjectIPC(this);
			m_SubscriptionTable[table][type][subscriber->Name()] = callback;

			m_Diagnostics->Log(Logger::Level::Information, "%s Subscribed on %s of type %s", subscriber->Name().c_str(), table.c_str(), type.c_str());
			return true;
		}

		bool IPCBase::Unsubscribe(std::string table, SubscribablePtr subscriber, std::string type)
		{
			SubscriberName subscriberName = subscriber->Name();

			if (m_SubscriptionTable[table][type].find(subscriberName) == m_SubscriptionTable[table][type].end())
			{
				return false;
			}		

			m_SubscriptionTable[table][type].erase(subscriberName);
			m_Diagnostics->Log(Logger::Level::Information, "%s Unsubscribed from %s of type %s", subscriber->Name().c_str(), table.c_str(), type.c_str());

			return true;
		}

		std::uint8_t IPCBase::GenerateSequenceNumber()
		{
			static std::uint8_t sequenceNumber = 0;
			++sequenceNumber == 0 ? sequenceNumber = 1 : sequenceNumber;
			return sequenceNumber;
		}

		void IPCBase::SendToTransport(std::vector<unsigned char> data)
		{
			m_Transport->Send(data);
		}

		std::vector<unsigned char> IPCBase::ReceiveFromTransport()
		{
			return m_Transport->Receive();
		}

		void IPCBase::OnReceive(IPCMessagePtr message)
		{
			const std::string source = message->Source();
			const std::string destination = message->Destination();
			const std::string type = message->Type();

			m_Diagnostics->Log(Logger::Level::Debug, "Received message of type %s from %s", type.c_str(), source.c_str());

			Subscriber messageSubscribers = m_SubscriptionTable[MESSAGE_TABLE][type];
			Subscriber sourceSubscribers = m_SubscriptionTable[SOURCE_TABLE][source];

			std::vector<Callback_t> callbacks;

			for (std::pair<std::string, Callback_t> p : messageSubscribers)
			{
				m_Diagnostics->Log(Logger::Level::Debug, "Forwarding message to %s", p.first.c_str());
				callbacks.push_back(p.second);
			}

			for (std::pair<std::string, Callback_t> p : sourceSubscribers)
			{
				m_Diagnostics->Log(Logger::Level::Debug, "Forwarding message to %s", p.first.c_str());
				callbacks.push_back(p.second);
			}

			for (Callback_t callback : callbacks)
			{
				if (callback)
				{
					callback(source, destination, message->ApplicationPayload());
				}
			}
		}
	}
}
