#pragma once

#include <string>

namespace Boggart
{
	namespace IPC
	{
		// Note: This class contains only the Message Subtypes
		// required by IPC subsytem. Application layers should 
		// handle their message types their respective modules/systems
		class Subtypes
		{
		private:
			Subtypes();

		public:
			static const std::string KeepAlive;
		};
	}
}