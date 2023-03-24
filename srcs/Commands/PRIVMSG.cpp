#include "Commands.hpp"

bool PRIVMSG::execute(Input const & cmd, Client * cli, IRCServer & serv) {
cout << "PRIVMSG command received" << endl;
    if (cmd.getTokens().size() < 2) {
        cout << "Error: Not enough parameters" << endl;
        cli->sendReply("461 Not enough parameters");
        return false;
    }
    // if (cmd.getTokens().size() > 3) {
    //     cout << "Error: Too many parameters" << endl;
    //     cli->sendReply("407 Too many targets");
    //     return false;
    // }
    string msg = cmd.getTokens()[2];
    for (size_t i = 3; i < cmd.getTokens().size(); i++) {
        msg += " " + cmd.getTokens()[i];
    }
    if (cmd.getTokens()[1][0] == '#') {
        Channel *chan = serv.getChannel(cmd.getTokens()[1]);
        if (!chan) {
            cout << "Error: No such channel" << endl;
            cli->sendReply("403 No such channel");
            return false;
        }
        cout << "Sending to channel " << chan->getName() << endl;
        chan->sendToAllOthers(":" + cli->getNickname() + " PRIVMSG " + chan->getName() + " " + msg + "\r\n", *cli);
        return true;
    }
    cout << "************* debug : " << cmd.getTokens()[1].substr(0) << " **************" << endl;
    Client *target = serv.getClientByNick(cmd.getTokens()[1].substr(0));
    if (!target) {
        cout << "Error: No such nick" << endl;
        cli->sendReply("401 No such nick");
        return false;
    }
    // if (target->getNickname() != cli->getChatwith()) {
    //     cli->setChatwith(target->getNickname());
    //     target->setChatwith(cli->getNickname());
    //     cout << "Creating a new chat beetwin " << cli->getNickname() << " and " << target->getNickname() << endl;
    //     target->sendReply(":" + cli->getNickname() + "!" + cli->getUsername() + "@" + cli->getHostname() + " 331 " + cli->getNickname() + " " + target->getNickname() + " : no topic is set");
    // }
        // cout << "Sending to client " << cli->getFd() << " " << cli->getNickname() << endl;
        // cli->sendReply(":" + cli->getNickname() + "!" + cli->getUsername() + "@" + cli->getHostname() + " PRIVMSG " + target->getNickname() + " " + cmd.getTokens()[2]);
        cout << "Sending to target number " << target->getFd() << "  nickname :" << target->getNickname() << endl;
        target->sendReply(":" + cli->getNickname() + " PRIVMSG " + cli->getNickname() + " " + msg + "\r\n");
        return true;
}
