#include "Commands.hpp"

bool JOIN::execute(Input const & cmd, Client * cli, IRCServer & serv) {
	
	string const & chanName = cmd.getTokens()[1];

	if (cmd.getTokens().size() < 2) {
		cli->sendReply("461 Not enough parameters");
		return false;
	}
	if (chanName[0] != '#') {
		cli->sendReply("403 No such channel");
		return false;
	}

	Channel *chan = serv.getChannel(chanName);

	if (!chan) {
		if (cmd.getTokens().size() == 3 && (atoi(cmd.getTokens()[2].c_str()) == PRIVATE || atoi(cmd.getTokens()[2].c_str()) == INVITE_ONLY || atoi(cmd.getTokens()[2].c_str()) == PRIVATE_WITH_INVITE))
			serv.createChannel(chanName, atoi(cmd.getTokens()[2].c_str()));
		else
			serv.createChannel(chanName, PUBLIC);
		chan = serv.getChannel(chanName);
		// cout << "Channel " << chanName << " created mode = " << chan->getMode() << endl;
		chan->setOperator(cli->getNickname());
	}
	if (chan->getMode() != PUBLIC && chan->getOperator() != cli->getNickname() && chan->getStrAllInvite().find(cli->getNickname()) == string::npos) {
		cout << "Error: Cannot join channel (+i) channel mode = " << chan->getMode() << endl;
		cli->sendReply("473 Cannot join channel (+i)\r\n");
		return false;
	}
	chan->addUser(cli);
	chan->sendToAll(":" + cli->getNickname() + "!" + cli->getUsername() + "@" + cli->getHostname() + " JOIN " + chanName + "\r\n");

    if (!chan->getTopic().empty())
        cli->sendReply("332 " + cli->getNickname() + " " + chanName + " :" + chan->getTopic() + "\r\n");

    cli->sendReply(":" + string(SERVER_NAME) + " 353 " + cli->getNickname() + " = " + chanName + " :" + chan->getStrAllUsers() + "\r\n");
    cli->sendReply(":" + string(SERVER_NAME) + " 366 " + cli->getNickname() + " " + chan->getName() + " :End of NAMES list\r\n");
    return true;
}