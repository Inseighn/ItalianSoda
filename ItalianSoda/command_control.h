#pragma once
#include "irc.h"
#include <string>

class command_control
{
public:

	command_control(irc*);
	~command_control();
	int command_process(std::string);

private:
	irc * irc_connection;
};

