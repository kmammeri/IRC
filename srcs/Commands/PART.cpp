#include "Commands.hpp"

bool PART::execute(Input const & cmd, Client * cli, IRCServer & serv) {

    if (cmd.getTokens().size() < 2) {
        cli->sendReply("461" + cli->getNickname() + " :Not enough parameters");
        return false;
    }
    if (serv.getChannel(cmd.getTokens()[1]))
    {
        serv.getChannel(cmd.getTokens()[1])->sendToAll(":" + cli->getNickname() + " PART " + cmd.getTokens()[1]);
        serv.getChannel(cmd.getTokens()[1])->removeUser(cli);
    }
    return true;
}