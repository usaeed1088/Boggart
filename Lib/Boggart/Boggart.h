#pragma once

// Timers
#include <Timer/Manager/SoftTimerManager/SoftTimerManager.h>

// Loggers
#include <Logger/Console/Console.h>

// Diagnostics
#include <Diagnostics/Diagnostics/Diagnsotics.h>

// IPCs
#include <IPC/Asynchronous/Asynchronous.h>
#include <IPC/Subscribable/Subscribable.h>

// Transports
#include <Transport/InProcess/InProcess.h>
#include <Transport/TCP/Server/Server.h>
#include <Transport/TCP/Client/Client.h>

#include <memory>

namespace Boggart
{
	class Boggart : std::enable_shared_from_this<Boggart>
	{
	private:
		std::shared_ptr<IPC::IPCBase> m_IPC;
		std::shared_ptr<Logger::LoggerBase> m_Logger;
		std::shared_ptr<Timer::ManagerBase> m_TimerManager;
		std::shared_ptr<Transport::TransportBase> m_Transport;

		static std::vector<Boggart*> s_Boggarts;

		Diagnostics m_Diagnostics;

	public:
		Boggart(std::string name);
		~Boggart();

		void InjectIPC(std::shared_ptr<IPC::IPCBase> ipc);
		void InjectLogger(std::shared_ptr<Logger::LoggerBase> logger);
		void InjectTimerManager(std::shared_ptr<Timer::ManagerBase> timerManager);
		void InjectTransport(std::shared_ptr<Transport::TransportBase> transport);

		static void Start();

		IPC::IIPCPtr IPC();
		Logger::ILoggerPtr Logger();
		Timer::IManagerPtr TimerManager();

	private:
		void Process();

		void InjectDependencies();
		bool StartComponents();
	};
}