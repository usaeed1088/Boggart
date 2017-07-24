#include "Console.h"

#include <iostream>

namespace Boggart
{
	namespace Logger
	{
		Console::Console()
		{

		}

		Console::~Console()
		{

		}

		void Console::_OnLog(std::string data)
		{
			std::cout << data << std::endl;
		}
	}
}