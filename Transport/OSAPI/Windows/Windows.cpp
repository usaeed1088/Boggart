#include "Windows.h"

#include <Windows.h>
#include <WinSock.h>
#pragma comment(lib, "ws2_32.lib")

namespace Transport
{
	static inline SOCKADDR_IN SocketAddressToSOCKADDR_IN(const SocketAddress& addr)
	{
		SOCKADDR_IN sockAddr_in = {};
		int length_SOCKADDR_IN = sizeof(SOCKADDR_IN);
		sockAddr_in.sin_family = AF_INET;								/* set the type of connection to TCP/IP */
		sockAddr_in.sin_addr.s_addr = inet_addr(addr.Address.c_str());
		sockAddr_in.sin_port = htons(addr.Port);

		return sockAddr_in;
	}

	Windows::Windows()
	{

	}

	Windows::~Windows()
	{

	}

	// Socket API
	DataType::SocketId Windows::SocketOpen(SocketFamily family, SocketType type, int protocol)
	{
		WSADATA webservicesdata = {};				/* Declare WSAData */
		WORD winsockVersion = MAKEWORD(2, 0);		/* Winsock 2.0 */

		if (WSAStartup(winsockVersion, &webservicesdata) != 0)
		{
			return -1;
		}

		int socketFamily = 0;
		int socketType = 0;

		switch (family)
		{
		case SocketFamily::InterNetwork:
			socketFamily = AF_INET;
			break;
		}

		switch (type)
		{
		case SocketType::Stream:
			socketType = SOCK_STREAM;
			break;
		case SocketType::Datagram:
			socketType = SOCK_DGRAM;
			break;
		}

		return ::socket(socketFamily, socketType, protocol);
	}

	bool Windows::SocketClose(int socket)
	{
		return ::closesocket(socket) == 0;
	}

	bool Windows::SocketBind(int socket, const SocketAddress& addr)
	{
		SOCKADDR_IN sockAddr_in = SocketAddressToSOCKADDR_IN(addr);

		return ::bind(socket, (sockaddr*)&sockAddr_in, sizeof(SOCKADDR)) == 0;
	}

	bool Windows::SocketListen(int socket, int nClients)
	{
		return ::listen(socket, nClients) == 0;
	}

	DataType::SocketId Windows::SocketAccept(int socket, const SocketAddress& addr)
	{
		SOCKADDR_IN sockAddr_in = SocketAddressToSOCKADDR_IN(addr);
		int length_SOCKADDR_IN = sizeof(SOCKADDR_IN);

		return ::accept(socket, (sockaddr*)&sockAddr_in, &length_SOCKADDR_IN);
	}

	bool Windows::SocketConnect(int socket, const SocketAddress& sock_in)
	{
		SOCKADDR_IN sockAddr_in = SocketAddressToSOCKADDR_IN(sock_in);

		return ::connect(socket, (sockaddr*)&sockAddr_in, sizeof(SOCKADDR_IN)) == 0;
	}

	bool Windows::SocketIOControl(int socket, SocketControl control, unsigned long arg)
	{
		int cmd = 0;
		int so_broadcast = TRUE;
		switch (control)
		{
		case SocketControl::NonBlocking:
			cmd = FIONBIO;
			return ioctlsocket(socket, cmd, &arg) == 0;
		case SocketControl::Broadcast:
			cmd = SO_BROADCAST;
			return ::setsockopt(socket, SOL_SOCKET, SO_BROADCAST, (const char*)&so_broadcast, sizeof so_broadcast) == 0;
		default:
			return false;
			break;
		}
	}

	bool Windows::SocketSend(int socket, const DataType::Bytes& data)
	{
		std::vector<char> buffer(data.begin(), data.end());
		return ::send(socket, &buffer[0], buffer.size(), 0) == data.size();
	}

	bool Windows::SocketSendTo(int socket, const DataType::Bytes& data, const SocketAddress& sendToAddress)
	{
		SOCKADDR_IN sockAddr_in = SocketAddressToSOCKADDR_IN(sendToAddress);
		std::vector<char> buffer(data.begin(), data.end());
		return ::sendto(socket, &buffer[0], buffer.size(), 0, (sockaddr*)&sockAddr_in, sizeof(SOCKADDR_IN)) == data.size();
	}

	DataType::Bytes Windows::SocketReceive(int socket)
	{
		const int ReceiveBufferLength = 1024 * 10; //10KB
		char buffer[ReceiveBufferLength] = {};
		int n = ::recv(socket, buffer, ReceiveBufferLength, 0);
		if (n > 0)
		{
			return DataType::Bytes(buffer, buffer + n);
		}
		else
		{
			return DataType::Bytes();
		}
	}

	DataType::Bytes Windows::SocketReceiveFrom(int socket, const SocketAddress& recvFrom)
	{
		SOCKADDR_IN sockAddr_in = SocketAddressToSOCKADDR_IN(recvFrom);
		int sizeOf_SOCKADDR_IN = sizeof(SOCKADDR_IN);

		const int ReceiveBufferLength = 1024 * 10; //10KB
		char buffer[ReceiveBufferLength] = {};

		int n = ::recvfrom(socket, buffer, ReceiveBufferLength, 0, (sockaddr*)&sockAddr_in, (int*)&sizeOf_SOCKADDR_IN);

		if (n > 0)
		{
			return DataType::Bytes(buffer, buffer + n);
		}
		else if (n == SOCKET_ERROR)
		{
			int err = WSAGetLastError();
			return DataType::Bytes();
		}

		return DataType::Bytes();
	}
}