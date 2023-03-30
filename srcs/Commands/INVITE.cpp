#include "Commands.hpp"

bool  INVITE::execute(Input const & cmd, Client * cli, IRCServer & serv)
{
    if (cmd.getTokens().size() < 3) {
        cli->sendReply("461" + cli->getNickname() + " :Not enough parameters\r\n");
        return false;
    }
    if (serv.getChannel(cmd.getTokens()[2]))
    {
        Client *target = serv.getClientByNick(cmd.getTokens()[1]);
        if (cli->getNickname() == serv.getChannel(cmd.getTokens()[2])->getOperator() || serv.getChannel(cmd.getTokens()[2])->getMode() == PUBLIC || serv.getChannel(cmd.getTokens()[2])->getMode() == INVITE_ONLY)
        {
            if (target)
            {
                string msg = ":" + cli->getNickname() + " INVITE " + cmd.getTokens()[1] + " " + cmd.getTokens()[2];
                serv.getChannel(cmd.getTokens()[2])->sendToAll(msg + "\r\n");
                target->sendReply(msg + "\r\n");
                serv.getChannel(cmd.getTokens()[2])->addInvite(target);
                return true;
            }
        }
    }
    return false;
}