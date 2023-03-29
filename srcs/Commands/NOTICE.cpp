#include "Commands.hpp"

bool NOTICE::execute(Input const & cmd, Client * cli, IRCServer & serv) {
cout << "NOTICE command received" << endl;
    if (cmd.getTokens().size() < 2) {
        cout << "Error: Not enough parameters" << endl;
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
            cout << "Error: No such channel" << endl;
            cli->sendReply("403 No such channel\r\n");
            return false;
        }
        cout << "Sending to channel " << chan->getName() << endl;
        chan->sendToAllOthers(":" + cli->getNickname() + " NOTICE " + chan->getName() + " " + msg + "\r\n", *cli);
        return true;
    }
    Client *target = serv.getClientByNick(cmd.getTokens()[1].substr(0));
    if (!target) {
        cout << "Error: No such nick" << endl;
        cli->sendReply("401 No such nick\r\n");
        return false;
    }
    cout << "Sending to target number " << target->getFd() << "  nickname :" << target->getNickname() << endl;
    target->sendReply(":" + cli->getNickname() + " NOTICE " + cli->getNickname() + " " + msg + "\r\n");
    return true;
}
