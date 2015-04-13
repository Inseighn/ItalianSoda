#include "command_control.h"


command_control::command_control(irc  * irc_con)
{
	irc_connection = irc_con;
}


command_control::~command_control()
{
}

int command_control::command_process(std::string inc_command){

}