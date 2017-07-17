#pragma once

#include <ostream>
#include <cstdint>

namespace Boggart
{
	namespace Timer
	{
		class Type
		{
		public:
			typedef std::int16_t Value_t;

		private:
			Value_t m_Value;

		public:
			Type(Value_t value);

			static const Value_t OneShot = 10;
			static const Value_t Periodic = 20;

			void operator=(Type& type);
			bool operator==(Type& type);
			operator int();
			friend std::ostream& operator<<(std::ostream& os, Type& type);
		};
	}
}