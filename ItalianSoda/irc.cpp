#include "irc.h"


irc::irc()
{
	srand(time(NULL));
	USER = "IS" + std::to_string(rand());
	NICK = IRC_NICK_PREFIX + std::to_string(rand());
}


irc::~irc()
{
	if (irc_message_loop_thread.joinable()){ irc_message_loop_thread.join(); }
}
void irc::irc_send_privmsg(std::string msg){
	if (irc_connection.sock_connected()){
		irc_connection.socket_send("PRIVMSG " + std::string(IRC_CHANNEL) + " :" + msg + IRC_ENDL);
		std::cout << "SENT: " << "PRIVMSG " + std::string(IRC_CHANNEL) + " :" + msg << std::endl;
	}
}
void irc::irc_send_privmsg(std::string msg, std::string user){
	if (irc_connection.sock_connected()){
		irc_connection.socket_send("PRIVMSG " + user + ":" + msg + IRC_ENDL);
	}
}
void irc::irc_message_loop(){
	int recv_result;
	std::string result;
	do{
		recv_result = irc_connection.socket_recv(result);
		if (result.find("PING :") != std::string::npos){
			std::cout << result << std::endl;
			int pos = result.find(":");
			if (pos != std::string::npos){
				irc_connection.socket_send("PONG " + result.substr(pos) + IRC_ENDL);
				std::cout << "PONG SENT " << result.substr(pos) << std::endl;
			}
		}
			std::cout << result << std::endl;
		result.clear();
	} while (recv_result > 0);
}

void irc::irc_start(){
	this->irc_connection.connect_socket(IRC_SERVER, IRC_PORT);
	if (this->irc_connection.sock_connected()){
		irc_message_loop_thread = std::thread(&irc::irc_message_loop, this);
		irc_set_user(USER);
		irc_set_nick(NICK);
		irc_change_channel(IRC_CHANNEL);
	}
}
void irc::irc_change_channel(std::string channel){
	if (this->irc_connection.sock_connected()){
		irc_connection.socket_send("JOIN " + channel + IRC_ENDL);
	}
}
void irc::irc_set_user(std::string user){
	if (this->irc_connection.sock_connected()){
		irc_connection.socket_send("USER " + user + " 0 *: IS" + IRC_ENDL);
	}
}
void irc::irc_set_nick(std::string nick){
	if (this->irc_connection.sock_connected()){
		irc_connection.socket_send("NICK " + nick + " 0 *: IS" + IRC_ENDL);
	}
}