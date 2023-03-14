#include "Commands.hpp"

bool PRIVMSG::execute(Input const & cmd, Client * cli, IRCServer & serv) {
cout << "PRIVMSG command received" << endl;
    if (cmd.getTokens().size() < 3) {
        cout << "Error: Not enough parameters" << endl;
        cli->sendReply("461 Not enough parameters");
        return false;
    }
    if (cmd.getTokens().size() > 3) {
        cout << "Error: Too many parameters" << endl;
        cli->sendReply("407 Too many targets");
        return false;
    }
    if (cmd.getTokens()[1][0] == '#') {
        Channel *chan = serv.getChannel(cmd.getTokens()[1]);
        if (!chan) {
            cout << "Error: No such channel" << endl;
            cli->sendReply("403 No such channel");
            return false;
        }
        cout << "Sending to channel " << chan->getName() << endl;
        chan->sendToAll(":" + cli->getNickname() + " PRIVMSG" + chan->getName() + cmd.getTokens()[2]);
        return true;
    }
    Client *target = serv.getClientByNick(cmd.getTokens()[1].substr(1));
    if (!target) {
        cout << "Error: No such nick" << endl;
        cli->sendReply("401 No such nick");
        return false;
    }
        cout << "Sending to client " << target->getFd() << " " << target->getNickname() << endl;
        target->sendReply(":" + cli->getNickname() + "!" + cli->getUsername() + "@" + cli->getHostname() + " PRIVMSG " + target->getNickname() + " " + cmd.getTokens()[2]);
        return true;
}
