
#include "Commands.hpp"

bool PASS::execute(Input const & cmd, Client * cli, IRCServer & serv) {
	
	if (cli->isRegistered()) {
		cli->sendReply("462", "You are already registered");
		return true;
	}
	if (cli->isAuthentificated())
		return true;
	if (cmd.getTokens().size() < 2) {
		cli->sendReply("461", "Not enough parameters");
		return false;
	}
	if (cmd.getTokens()[1] == serv.getPassword()) {
		cli->setAuthentification(true);
		return true;
	}
	else {
		cli->sendReply("464", "Password incorrect");
		return false;
	}
	return false;
}