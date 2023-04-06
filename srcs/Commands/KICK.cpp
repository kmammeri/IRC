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
            if (serv.getChannel(cmd.getTokens()[1])->getUsers().size() != 0 && serv.getChannel(cmd.getTokens()[1])->getOperator() == cmd.getTokens()[2])
            {
                serv.getChannel(cmd.getTokens()[1])->setOperator(serv.getChannel(cmd.getTokens()[1])->getFirstUser());
                serv.getChannel(cmd.getTokens()[1])->sendToAll(":" + cli->getNickname() + " MODE " + cmd.getTokens()[1] + " +o " + serv.getChannel(cmd.getTokens()[1])->getFirstUser() + "\r\n");
                serv.getChannel(cmd.getTokens()[1])->sendToAll(":" + cli->getNickname() + " MODE " + cmd.getTokens()[1] + " -o " + cli->getNickname() + "\r\n");
            }
            if (serv.getChannel(cmd.getTokens()[1])->getUsers().size() == 0)
            {
                serv.deleteChannel(cmd.getTokens()[1]);
            }
        }
        else
            cli->sendReply("401 "+ cli->getNickname() + " :No such nick/channel\r\n");
    }
    return true;
}