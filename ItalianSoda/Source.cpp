#include "irc.h"
int main(int argc, char argv[]){
	irc irc_client;
	irc_client.irc_start();

	irc_client.irc_send_privmsg("hey");
	std::string first("12345");
	std::cout << (first.find("0") != std::string::npos) << FALSE << TRUE << std::endl;
}