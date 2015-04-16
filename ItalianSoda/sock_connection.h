#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <string>

#include <stdlib.h>

#define WIN32_LEAN_AND_MEAN



const int BUFLEN = 512;
class sock_connection
{
public:
	sock_connection();
	~sock_connection();

	void connect_socket(PCSTR,PCSTR);
	void socket_send(std::string data);


	int socket_recv(std::string &buffer);

	bool sock_connected() const { return _sock_connected; }


private:


	SOCKET _connection_socket = INVALID_SOCKET;

	PCSTR SERVER, PORT;

	bool _sock_connected = false;
};

