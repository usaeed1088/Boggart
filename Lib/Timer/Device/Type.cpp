#include "Type.h"

#include <string>

namespace Boggart
{
	namespace Timer
	{
		Type::Type(Value_t value):
			m_Value(value)
		{

		}

		void Type::operator=(Type& type)
		{
			m_Value = type.m_Value;
		}

		bool Type::operator==(Type& type)
		{
			return m_Value == type.m_Value;
		}

		Type::operator int()
		{
			return m_Value;
		}

		std::ostream& operator<<(std::ostream& os, Type& type)
		{
			switch (type.m_Value)
			{
			case Type::OneShot:
				os << std::string("One Shot");
				break;
			case Type::Periodic:
				os << std::string("Periodic");
				break;
			default:
				os << std::string("Unknown");
				break;
			}

			return os;
		}
	}
}