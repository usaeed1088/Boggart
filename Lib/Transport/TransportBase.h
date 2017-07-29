#pragma once

#include <Common/Patterns/DependencyInjection/DependencyInjectionBase.h>

#include "ITransport.h"

namespace Boggart
{
	namespace Transport
	{
		class TransportBase : public ITransport, public DependencyInjectionBase<TransportBase>
		{
		private:
			std::string m_Id;

		protected:
			TransportBase(std::string moduleName, std::string id);

		public:
			virtual ~TransportBase() override;

			bool Open() override;

			bool Close() override;

			std::string Id() override;

			bool Send(const std::vector<unsigned char>& data) override;

			std::vector<unsigned char> Receive() override;

		protected:
			virtual bool OnOpen() = 0;

			virtual bool OnClose() = 0;

			virtual bool OnSend(const std::vector<unsigned char>& data) = 0;

			virtual std::vector<unsigned char> OnReceive() = 0;
		};
	}
}