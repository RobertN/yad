#ifndef NETWORKCONNECTION_HPP
#define NETWORKCONNECTION_HPP

#include <string>

class NetworkConnection
{
	public:
		enum ConnectionErrors
		{
			NOT_CONNECTED = -1
		};

		NetworkConnection();
		virtual ~NetworkConnection();

		bool connected() { return m_connected; }
		bool establish(std::string hostname, unsigned int port);
		void disconnect();

		size_t send(std::string message);
		std::string recv(size_t bytes);
	private:
		int m_socket;
		bool m_connected;
};

#endif
