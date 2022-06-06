#pragma once
#include <SFML\Network.hpp>

class Socket
{
public:
	Socket();
	~Socket() = default;
	void Listner();
private:
	sf::IpAddress m_ip;
	sf::TcpSocket m_socket;
	char m_connectionType, m_mode;
	char m_buffer[2000];
	std::size_t m_recieved;
};
