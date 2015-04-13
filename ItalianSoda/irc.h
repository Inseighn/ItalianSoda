#pragma once
#include "sock_connection.h"
#include "command_control.h"
#include <random>
#include <iostream>
#include <time.h>
#include <thread>

#define IRC_SERVER "irc.rizon.io"
#define IRC_PORT "6660"
#define IRC_CHANNEL "#aaron31494"
#define IRC_COMMAND_PREFIX "."
#define IRC_NICK_PREFIX "IS"

#define IRC_ENDL "\r\n"

class irc
{
public:
	irc();
	~irc();

	void irc_send_privmsg(std::string msg);
	void irc_send_privmsg(std::string msg, std::string user);

	void irc_change_channel(std::string channel);
	void irc_set_nick(std::string nick);
	void irc_set_user(std::string userstr);

	void irc_start();

private:
	std::string USER, HOST, NICK;

	std::thread irc_message_loop_thread;

	sock_connection irc_connection;
	command_control command_center;

	void irc_message_loop();
};

