
#include "Commands.hpp"

bool USER::execute(Input const & cmd, Client * cli, IRCServer & serv) {
	
	(void)serv;
	if (cli->getUsername() != "" || cli->isRegistered() == true) {
		cli->sendReply("462 You are already registered");
		return false;
	}
	if (cmd.getTokens().size() < 2) {
		cli->sendReply("461 Not enough parameters");
		return false;
	}
	if (serv.getClientByUser(cmd.getTokens()[1])) {
		cli->sendReply("433 Username is already in use");
		return false;
	}
	cli->setUsername(cmd.getTokens()[1]);
	if (cmd.getTokens().size() == 4) {
		cli->setServername(cmd.getTokens()[2]);
		cli->setRealname(cmd.getTokens()[4]);
	}
	return true;
}

