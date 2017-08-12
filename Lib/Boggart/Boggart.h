#pragma once

// Timers
#include <Timer/Manager/SoftTimerManager/SoftTimerManager.h>

// Loggers
#include <Logger/Console/Console.h>

// IPCs
#include <IPC/Asynchronous/Asynchronous.h>

// Transports
#include <Transport/InProcess/InProcess.h>
#include <Transport/TCP/Server/Server.h>
#include <Transport/TCP/Client/Client.h>

#include <memory>

namespace Boggart
{
	class Boggart
	{
	private:
		IPC::IIPCPtr m_IPC;
		Logger::ILoggerPtr m_Logger;
		Timer::IManagerPtr m_TimerManager;
		Transport::ITransportPtr m_Transport;

		std::vector<std::shared_ptr<Boggart>> m_Boggarts;

	public:
		Boggart();
		~Boggart();

		void InjectIPC(IPC::IIPCPtr ipc);
		void InjectLogger(Logger::ILoggerPtr logger);
		void InjectTimerManager(Timer::IManagerPtr timerManager);
		void InjectTransport(Transport::ITransportPtr transport);

		void InjectBoggart(std::shared_ptr<Boggart> boggart);

		void Start();

	private:
		void Process();
	};
}