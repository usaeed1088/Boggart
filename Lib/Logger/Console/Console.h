#pragma once

#include "../LoggerBase.h"

namespace Boggart
{
	namespace Logger
	{
		class Console : public LoggerBase
		{
		public:
			Console();
			~Console() override;

		private:
			void _OnLog(std::string data) override;
		};
	}
}