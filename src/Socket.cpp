#include "Socket.h"
#include <iostream>

Socket::Socket()
{
	std::cout << "Enter (s) for Server, Enter (c) for Client: " << std::endl;
	std::cin >> m_connectionType;
	m_ip = sf::IpAddress::getLocalAddress();
}

void Socket::Listner()
{
	if (m_connectionType == 's')
	{
		sf::TcpListener listner;
		listner.listen(2000);	//add enum
		listner.accept(m_socket);
		std::string msg = "connected to Server";
		m_socket.send(msg.c_str(), msg.length() + 1);
		m_mode = 's';
	}
	else if (m_connectionType == 'c')
	{
		m_socket.connect(m_ip, 2000);
		std::string msg = "connected to Client";
		m_socket.send(msg.c_str(), msg.length() + 1);
		m_mode = 'r';
	}
	m_socket.receive(m_buffer, sizeof(m_buffer), m_recieved);
	std::cout << m_buffer << std::endl;
	bool done = false;
	while (!done)
	{
		std::string msg;
		if (m_mode == 's')
		{
			std::getline(std::cin, msg);
			m_socket.send(msg.c_str(), msg.length() + 1);
			m_mode = 'r';
		}
		else if (m_mode = 'r')
		{
			m_socket.receive(m_buffer, sizeof(m_buffer), m_recieved);
			if (m_recieved > 0)
			{
				std::cout << "Received: " << m_buffer << std::endl;
				m_mode = 's';
			}
			
		}
	}
	system("pause");
}
