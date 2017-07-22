#include "IPCBase.h"

namespace Boggart
{
	namespace IPC
	{
		const std::string EVENT_TABLE("EVENTS");
		const std::string MESSAGE_TABLE("MESSAGES");
		const std::string SOURCE_TABLE("SOURCES");

		IPCBase::IPCBase(std::string moduleName, std::string myId):
			DependencyInjectionBase<IPCBase>(std::string("IPC"), moduleName),
			m_SubscriptionTable(),
			m_Transport(nullptr),
			m_MyId(myId)
		{

		}

		IPCBase::~IPCBase()
		{

		}

		void IPCBase::InjectTransport(Transport::ITransportPtr transport)
		{
			m_Transport = transport;
		}

		bool IPCBase::SubscribeEvent(SubscribablePtr subscriber, std::string type, Callback_t callback)
		{
			Subscribe(EVENT_TABLE, subscriber, type, callback);

			return OnSubscribeEvent(subscriber, type, callback);
		}

		bool IPCBase::SubscribeMessage(SubscribablePtr subscriber, std::string type, Callback_t callback)
		{
			Subscribe(MESSAGE_TABLE, subscriber, type, callback);

			return OnSubscribeMessage(subscriber, type, callback);
		}

		bool IPCBase::SubscribeSource(SubscribablePtr subscriber, std::string type, Callback_t callback)
		{
			Subscribe(SOURCE_TABLE, subscriber, type, callback);

			return OnSubscribeSource(subscriber, type, callback);
		}

		bool IPCBase::UnsubscribeEvent(SubscribablePtr subscriber, std::string type)
		{
			Unsubscribe(EVENT_TABLE, subscriber, type);

			return OnUnsubscribeEvent(subscriber, type);
		}

		bool IPCBase::UnsubscribeMessage(SubscribablePtr subscriber, std::string type)
		{
			Unsubscribe(MESSAGE_TABLE, subscriber, type);

			return OnUnsubscribeMessage(subscriber, type);
		}

		bool IPCBase::UnsubscribeSource(SubscribablePtr subscriber, std::string type)
		{
			Unsubscribe(SOURCE_TABLE, subscriber, type);

			return OnUnsubscribeSource(subscriber, type);
		}

		bool IPCBase::Unsubscribe(SubscribablePtr subscriber)
		{
			if (m_SubscriptionTable[EVENT_TABLE].find(subscriber) != m_SubscriptionTable[EVENT_TABLE].end())
			{
				m_SubscriptionTable[EVENT_TABLE].erase(subscriber);
			}

			if (m_SubscriptionTable[MESSAGE_TABLE].find(subscriber) != m_SubscriptionTable[MESSAGE_TABLE].end())
			{
				m_SubscriptionTable[MESSAGE_TABLE].erase(subscriber);
			}

			if (m_SubscriptionTable[SOURCE_TABLE].find(subscriber) != m_SubscriptionTable[SOURCE_TABLE].end())
			{
				m_SubscriptionTable[SOURCE_TABLE].erase(subscriber);
			}

			return true;
		}

		bool IPCBase::Send(std::string destination, Message::IMessagePtr message)
		{
			message->SequenceNumber(GenerateSequenceNumber());
			message->Destination(destination);
			message->Source(m_MyId);

			m_Diagnostics.Log(Logger::Level::Debug, "Sending Message Sequence Number [%d] to [%s]", (std::int32_t)message->SequenceNumber(), destination.c_str());

			// TODO: Handle Retransmissions

			return m_Transport->Send(message->Encode());
		}

		bool IPCBase::Subscribe(std::string table, SubscribablePtr subscriber, std::string type, Callback_t callback)
		{
			subscriber->InjectIPC(this);
			m_SubscriptionTable[table][subscriber][type] = callback;
			return true;
		}

		bool IPCBase::Unsubscribe(std::string table, SubscribablePtr subscriber, std::string type)
		{
			if (m_SubscriptionTable[table].find(subscriber) == m_SubscriptionTable[EVENT_TABLE].end())
			{
				return false;
			}

			if (m_SubscriptionTable[table][subscriber].find(type) == m_SubscriptionTable[EVENT_TABLE][subscriber].end())
			{
				return false;
			}

			m_SubscriptionTable[table][subscriber].erase(type);

			return true;
		}

		std::uint8_t IPCBase::GenerateSequenceNumber()
		{
			static std::uint8_t sequenceNumber = 0;
			++sequenceNumber == 0 ? sequenceNumber = 1 : sequenceNumber;
			return sequenceNumber;
		}
	}
}