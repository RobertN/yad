#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include "NetworkConnection.hpp"
#include <unistd.h>

NetworkConnection::NetworkConnection()
{
}

NetworkConnection::~NetworkConnection()
{
	if (m_connected)
	{
		close(m_socket);
		m_connected = false;
	}
}

bool NetworkConnection::establish(std::string hostname, unsigned int port)
{
	fprintf(stderr, "NetworkConnection::establish\n");

	struct sockaddr_in addr;
	struct hostent *hp;

	hp = gethostbyname(hostname.c_str());
	if (!hp)
	{
		perror("gethostbyname");

		return false;
	}

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
	addr.sin_port = htons(port);

	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == -1)
	{
		perror("socket");
		return false;
	}

	int connected = connect(m_socket, (struct sockaddr*) &addr, sizeof(addr));
	if (connected == -1)
	{
		perror("connect");
		return false;
	}
	m_connected = true;
	return true;
}

size_t NetworkConnection::send(std::string message)
{
	fprintf(stderr, "NetworkConnection::send\n");

	if (!m_connected)
	{
		fprintf(stderr, "Not connected\n");
		return -1;
	}

	int sent_bytes = ::send(m_socket, message.c_str(), message.length(), 0);
	if (sent_bytes == -1)
	{
		perror("send");
		return -1;
	}
	return sent_bytes;
}

std::string NetworkConnection::recv(size_t bytes)
{
	fprintf(stderr, "NetworkConnection::recv\n");

	char buf[bytes];
	int recvd_bytes = ::recv(m_socket, &buf, bytes, 0);
	if (recvd_bytes == -1)
	{
		perror("recv");
		return std::string("");
	}
	return std::string(buf);
}
