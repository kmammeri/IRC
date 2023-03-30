#include "Commands.hpp"

bool  NAMES::execute(Input const & cmd, Client * cli, IRCServer & serv)
{
    if (cmd.getTokens().size() < 2) {
        cli->sendReply("461" + cli->getNickname() + " :Not enough parameters\r\n");
        return false;
    }
    if (serv.getChannel(cmd.getTokens()[1]))
    {
        cli->sendReply(":" + string(SERVER_NAME) + " 353 " + cli->getNickname() + " = " + serv.getChannel(cmd.getTokens()[1])->getName() + " :" + serv.getChannel(cmd.getTokens()[1])->getStrAllUsers() + "\r\n");
        cli->sendReply(":" + string(SERVER_NAME) + " 366 " + cli->getNickname() + " " + serv.getChannel(cmd.getTokens()[1])->getName() + " :End of NAMES list\r\n");
    }
    return true;
}