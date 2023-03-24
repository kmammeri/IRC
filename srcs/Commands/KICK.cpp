#include "Commands.hpp"

bool KICK::execute(Input const & cmd, Client * cli, IRCServer & serv) {
    if (cmd.getTokens().size() < 2) {
        cli->sendReply("461" + cli->getNickname() + " :Not enough parameters");
        return false;
    }
    if (serv.getChannel(cmd.getTokens()[1]) && cli->getNickname() == serv.getChannel(cmd.getTokens()[1])->getOperator())
    {
        Client *target = serv.getClientByNick(cmd.getTokens()[2]);
        if (target)
            serv.getChannel(cmd.getTokens()[1])->sendToAll("KICK " + cmd.getTokens()[1] + " " + cmd.getTokens()[2]);
        {   serv.getChannel(cmd.getTokens()[1])->removeUser(target);
        }
    }
    return true;
}