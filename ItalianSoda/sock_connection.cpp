#include "sock_connection.h"


sock_connection::sock_connection()
{

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

}

int sock_connection::socket_recv(std::string &buffer){
	if (_sock_connected){
		char buf[BUFLEN];
		int len = recv(_connection_socket, buf, BUFLEN, 0);
		_sock_connected = (len != 0);
		if (len > 0){
			buffer.append(buf, 0, len);
		}
		return len;
	}
	return -1;
}
void sock_connection::socket_send(std::string data){
	if (_sock_connected){
		_sock_connected = (send(_connection_socket, data.c_str(), data.length(), 0) != SOCKET_ERROR);
	}
}
sock_connection::~sock_connection()
{
	if (_sock_connected)
	{
		closesocket(_connection_socket);
	}
	WSACleanup();
}

void sock_connection::connect_socket(PCSTR SERVER, PCSTR PORT){
	if (strlen(SERVER) <= 0 || strlen(PORT) <= 0){
		return;
	}
	this->SERVER = SERVER;
	this->PORT = PORT;
	struct addrinfo *result = NULL,
		hints;
	int iresult;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	iresult = getaddrinfo(SERVER, PORT, &hints, &result);
	if (iresult != 0){
		WSACleanup();
		return;
	}
	_connection_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (_connection_socket == INVALID_SOCKET){
		WSACleanup();
		return;
	}
	iresult = connect(_connection_socket, result->ai_addr, (int)result->ai_addrlen);
	if (iresult == SOCKET_ERROR){
		closesocket(_connection_socket);
		WSACleanup();
	}

	freeaddrinfo(result);
	_sock_connected = (_connection_socket != INVALID_SOCKET);
}