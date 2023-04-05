#include "Commands.hpp"

bool PRIVMSG::execute(Input const & cmd, Client * cli, IRCServer & serv) {
    if (cmd.getTokens().size() < 2) {

        cli->sendReply("461 Not enough parameters\r\n");
        return false;
    }
    string msg = cmd.getTokens()[2];
    for (size_t i = 3; i < cmd.getTokens().size(); i++) {
        msg += " " + cmd.getTokens()[i];
    }
    if (cmd.getTokens()[1][0] == '#') {
        Channel *chan = serv.getChannel(cmd.getTokens()[1]);
        if (!chan) {
            cli->sendReply("403 No such channel\r\n");
            return false;
        }
        if (chan->getStrAllUsers().find(cli->getNickname()) == string::npos) {
            cli->sendReply("404 Cannot send to channel\r\n");
            return false;
        }
        chan->sendToAllOthers(":" + cli->getNickname() + " PRIVMSG " + chan->getName() + " " + msg + "\r\n", cli->getNickname());
        return true;
    }
    Client *target = serv.getClientByNick(cmd.getTokens()[1].substr(0));
    if (!target) {
        cli->sendReply("401 No such nick\r\n");
        return false;
    }
    target->sendReply(":" + cli->getNickname() + " PRIVMSG " + cli->getNickname() + " " + msg + "\r\n");
    return true;
}
