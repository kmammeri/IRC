#include "Commands.hpp"

bool    PING::execute(Input const & cmd, Client * cli, IRCServer & serv)
{
    (void)serv;
    if (cmd.getTokens().size() < 2) {
        cli->sendReply("461" + cli->getNickname() + " :Not enough parameters\r\n");
        return false;
    }
    cli->sendReply("PONG " + cmd.getTokens()[1] + "\r\n");
    return true;
}