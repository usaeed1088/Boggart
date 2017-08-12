#include "Boggart.h"

namespace Boggart
{
	Boggart::Boggart():
		m_IPC(nullptr),
		m_Logger(nullptr),
		m_TimerManager(nullptr),
		m_Transport(nullptr)
	{

	}

	Boggart::~Boggart()
	{

	}

	void Boggart::InjectIPC(IPC::IIPCPtr ipc)
	{
		m_IPC = ipc;
	}

	void Boggart::InjectLogger(Logger::ILoggerPtr logger)
	{
		m_Logger = logger;
	}

	void Boggart::InjectTimerManager(Timer::IManagerPtr timerManager)
	{
		m_TimerManager = timerManager;
	}

	void Boggart::InjectTransport(Transport::ITransportPtr transport)
	{
		m_Transport = transport;
	}

	void Boggart::InjectBoggart(std::shared_ptr<Boggart> boggart)
	{
		m_Boggarts.push_back(boggart);
	}

	void Boggart::Start()
	{

	}

	void Boggart::Process()
	{

	}
}