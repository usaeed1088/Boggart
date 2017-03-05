#pragma once

#include "../../Physical.h"
#include "../../../OSAPI/Socket/Socket.h"

namespace Transport
{
	namespace TCP
	{
		class Client : public Physical
		{
		private:
			mutable Socket m_Socket;
			SocketAddress m_ServerAddress;

		public:
			Client(SocketAddress serverAddress);
			~Client();

			void Send(const DataType::Bytes& data) const override;
			DataType::Bytes Receive() const override;

		private:
			void Process() const override;

		private:
			bool Open();
			void Close();
		};
	}
}