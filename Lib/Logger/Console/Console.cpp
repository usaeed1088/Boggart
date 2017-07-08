#include "Console.h"

#include <iostream>

namespace Boggart
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