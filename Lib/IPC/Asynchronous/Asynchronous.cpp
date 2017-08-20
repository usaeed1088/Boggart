#include "Asynchronous.h"

namespace Boggart
{
	namespace IPC
	{
		Asynchronous::Asynchronous(std::string myId):
			IPCBase(std::string("Asynchronous"), myId)
		{

		}

		Asynchronous::~Asynchronous()
		{
			m_TimerManager->Destroy(m_ProcessingTimer);
		}

		bool Asynchronous::OnStart()
		{
			// TODO: Get Span from Configuration
			m_ProcessingTimer = m_TimerManager->Create(Timer::Span_t(10), Timer::Type_t::Periodic, std::bind(&Asynchronous::OnProcessingTimerExpired, this));
			return m_TimerManager->Start(m_ProcessingTimer);
		}

		bool Asynchronous::OnSend(IPCMessagePtr message)
		{
			m_OutgoingQueue.push(message->Encode());
			return true;
		}

		void Asynchronous::OnProcessingTimerExpired()
		{
			ProcessIncomingTransport();
			ProcessOutgoingQueue();
			ProcessIncomingQueue();
		}

		void Asynchronous::ProcessIncomingTransport()
		{
			std::vector<unsigned char> data;
			data = ReceiveFromTransport();
			while (!data.empty())
			{
				m_IncomingQueue.push(data);
				data = ReceiveFromTransport();
			}
		}

		void Asynchronous::ProcessOutgoingQueue()
		{
			while (!m_OutgoingQueue.empty())
			{
				std::vector<unsigned char> data = m_OutgoingQueue.front();
				SendToTransport(data);

				m_OutgoingQueue.pop();
			}
		}

		void Asynchronous::ProcessIncomingQueue()
		{
			while (!m_IncomingQueue.empty())
			{
				std::vector<unsigned char> data = m_IncomingQueue.front();

				IPCMessagePtr message(new IPCMessage(data));

				if(message->Valid())
				{
					OnReceive(message);
				}

				m_IncomingQueue.pop();
			}
		}
	}
}