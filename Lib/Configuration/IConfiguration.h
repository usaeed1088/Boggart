#pragma once

#include <Common/Patterns/DependencyInjection/IDependencyInjection.h>

#include <string>

namespace Boggart
{
	class IConfiguration : IDependencyInjection<IConfiguration>
	{
	public:
		virtual ~IConfiguration() {}

		virtual bool LoadFromFile(const std::string& path) = 0;

	protected:
		virtual bool LoadDefault() = 0;
	};
}