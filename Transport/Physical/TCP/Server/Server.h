#pragma once

#include "../../Physical.h"
#include "../../../OSAPI/Socket/Socket.h"

namespace Transport
{
	namespace TCP
	{
		class Server : public Physical
		{
		private:
			mutable Socket m_Socket;
			SocketAddress m_MyAddress;
			mutable std::vector<Socket> m_Clients;

		public:
			Server(SocketAddress myAddress);
			~Server() override;

			void Send(const DataType::Bytes& data) const override;
			DataType::Bytes Receive() const override;

			// Test function begins
			void Process();
			// Test function ends
		private:
			bool Open();
			void Close();
		};
	}
}