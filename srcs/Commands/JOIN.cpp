#include "Commands.hpp"

bool JOIN::execute(Input const & cmd, Client * cli, IRCServer & serv) {
	if (cmd.getTokens().size() < 2) {
		cli->sendReply("461 Not enough parameters");
		return false;
	}
	if (cmd.getTokens()[1][0] != '#') {
		cli->sendReply("403 No such channel");
		return false;
	}

	Channel *chan = serv.getChannel(cmd.getTokens()[1]);

	if (!chan) {
		serv.createChannel(cmd.getTokens()[1]);
		// serv.sendReplyToAllClientsInChannel(cmd.getTokens()[1], cli->getNickname() + " has joined " + cmd.getTokens()[1]);
	}
	chan->addUser(cli);
	// serv.sendReplyToAllClientsInChannel(cmd.getTokens()[1], cli->getNickname() + " has joined " + cmd.getTokens()[1]);
	return true;
}