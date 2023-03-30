#include "Commands.hpp"

bool KICK::execute(Input const & cmd, Client * cli, IRCServer & serv) {
    if (cmd.getTokens().size() < 2) {
        cli->sendReply("461" + cli->getNickname() + " :Not enough parameters\r\n");
        return false;
    }
    if (serv.getChannel(cmd.getTokens()[1]) && cli->getNickname() == serv.getChannel(cmd.getTokens()[1])->getOperator())
    {
        Client *target = serv.getClientByNick(cmd.getTokens()[2]);
        if (target)
        {
            string msg = ":" + cli->getNickname() + " KICK " + cmd.getTokens()[1] + " " + cmd.getTokens()[2];
            if (cmd.getTokens().size() > 3)
            {
                msg += " :";
                for (size_t i = 3; i < cmd.getTokens().size(); i++)
                    msg += " " + cmd.getTokens()[i];
            }
            serv.getChannel(cmd.getTokens()[1])->sendToAll(msg + "\r\n");
            serv.getChannel(cmd.getTokens()[1])->removeUser(target);
        }
    }
    return true;
}