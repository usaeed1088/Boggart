#pragma once

#include "../../DataType.h"

namespace Transport
{
	enum class SocketControl : unsigned char
	{
		Unknown = 0,
		NonBlocking = 1,		// FIONBIO
		Broadcast = 2,
	};

	enum class SocketFamily : unsigned char
	{
		Unknown = 0,
		InterNetwork = 1,		// INET
	};

	enum class SocketType : unsigned char
	{
		Unknown = 0,
		Stream = 1,				// Stream socket
		Datagram = 2,			// Datagram socket
	};

	struct SocketAddress
	{
		SocketAddress() : Address(""), Port(0) {}
		SocketAddress(DataType::Text address, int port) : Address(address), Port(port) { }
		DataType::Text Address;
		int Port;
	};
}