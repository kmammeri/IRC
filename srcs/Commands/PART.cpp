#include "Commands.hpp"

bool PART::execute(Input const & cmd, Client * cli, IRCServer & serv) {

    if (cmd.getTokens().size() < 2) {
        cli->sendReply("461" + cli->getNickname() + " :Not enough parameters\r\n");
        return false;
    }
    if (serv.getChannel(cmd.getTokens()[1]))
    {
        serv.getChannel(cmd.getTokens()[1])->removeUser(cli);
        if (serv.getChannel(cmd.getTokens()[1])->getUsers().size() != 0 && serv.getChannel(cmd.getTokens()[1])->getOperator() == cli->getNickname())
        {
            serv.getChannel(cmd.getTokens()[1])->setOperator(serv.getChannel(cmd.getTokens()[1])->getFirstUser());
            serv.getChannel(cmd.getTokens()[1])->sendToAll(":" + cli->getNickname() + " MODE " + cmd.getTokens()[1] + " +o " + serv.getChannel(cmd.getTokens()[1])->getFirstUser() + "\r\n");
            serv.getChannel(cmd.getTokens()[1])->sendToAll(":" + cli->getNickname() + " MODE " + cmd.getTokens()[1] + " -o " + cli->getNickname() + "\r\n");
        }
        if (serv.getChannel(cmd.getTokens()[1])->getUsers().size() != 0)
        {
            serv.getChannel(cmd.getTokens()[1])->sendToAll(":" + cli->getNickname() + " PART " + cmd.getTokens()[1] + "\r\n");
        }
        else
        {
            serv.deleteChannel(cmd.getTokens()[1]);
        }
        cli->sendReply(":" + cli->getNickname() + " PART " + cmd.getTokens()[1] + "\r\n");
    }
    return true;
}