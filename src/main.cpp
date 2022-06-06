#include "Menu.h"
#include "Socket.h"

int main()
{
	Socket socket;
	socket.Listner();
	Menu().run();
	return true;
}