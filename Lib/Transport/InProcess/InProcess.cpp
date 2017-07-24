#include "InProcess.h"

namespace Boggart
{
	namespace Transport
	{
		InProcess::InProcess():
			TransportBase(std::string("InProcess"))
		{
			s_Subscribers.push_back(this);
		}

		InProcess::~InProcess()
		{
			for (std::vector<InProcess*>::iterator it = s_Subscribers.begin(); it != s_Subscribers.end(); ++it)
			{
				if ((*it) == this)
				{
					s_Subscribers.erase(it);
					break;
				}
			}
		}

		bool InProcess::OnOpen()
		{
			return true;
		}

		bool InProcess::OnClose()
		{
			return true;
		}

		bool InProcess::OnSend(const std::vector<unsigned char>& data)
		{
			// Push to data queue of all subscribers but 'this'
			for (InProcess* process : s_Subscribers)
			{
				if (process != this)
				{
					process->Push(data);
				}
			}
			return true;
		}

		std::vector<unsigned char> InProcess::OnReceive()
		{
			std::lock_guard<std::mutex> lock(m_DataQueueLock);
			if (m_DataQueue.empty())
			{
				return std::vector<unsigned char>();
			}

			std::vector<unsigned char> data = m_DataQueue.front();
			m_DataQueue.pop();

			return data;
		}

		void InProcess::Push(const std::vector<unsigned char>& data)
		{
			std::lock_guard<std::mutex> lock(m_DataQueueLock);
			m_DataQueue.push(data);
		}
	}
}