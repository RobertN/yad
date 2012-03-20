#ifndef NETWORKCONNECTION_HPP
#define NETWORKCONNECTION_HPP

#include <string>

class NetworkConnection
{
	public:
		NetworkConnection();
		~NetworkConnection();

		bool establish(std::string hostname, unsigned int port);
		void disconnect();

		size_t send(std::string message);
		std::string recv(size_t bytes);
	private:
		int m_socket;
		bool m_connected;
};

#endif
