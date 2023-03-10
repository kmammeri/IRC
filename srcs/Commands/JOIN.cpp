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
		serv.createChannel(chanName);
		chan = serv.getChannel(chanName);
		chan->setOperator(cli->getNickname());
	}
	chan->addUser(cli);
	chan->sendToAll(":" + cli->getNickname() + "!" + cli->getUsername() + "@" + cli->getHostname() + " JOIN " +
                       chanName + "\r\n");

    if (!chan->getTopic().empty())
        cli->sendReply("332 " + cli->getNickname() + " " + chanName + " :" + chan->getTopic() + "\r\n");

    cli->sendReply(":" + string(SERVER_NAME) + " 353 " + cli->getNickname() + " = " + chanName + " :" + chan->getStrAllUsers() + "\r\n");
    cli->sendReply(":" + string(SERVER_NAME) + " 366 " + cli->getNickname() + " " + chan->getName() + " :End of NAMES list\r\n");
    return true;
}