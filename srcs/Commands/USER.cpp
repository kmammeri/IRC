
#include "Commands.hpp"

bool USER::execute(Input const & cmd, Client * cli, IRCServer & serv) {
	
	if (cli->getUsername() != "" || cli->isRegistered()) {
		cli->sendReply("462 You are already registered");
		return true;
	}
	if (cmd.getTokens().size() < 2) {
		cli->sendReply("461 Not enough parameters");
		return false;
	}
	if (cmd.getTokens().size() >= 2) {
		cli->setUsername(cmd.getTokens()[1]);
		return true;
	}
	(void)serv;
	return false;
}