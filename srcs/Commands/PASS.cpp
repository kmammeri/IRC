
#include "Commands.hpp"

bool PASS::execute(Input const & cmd, Client * cli, IRCServer & serv) {
	
	if (cli->isAuthentificated()) {
		cli->sendReply("462", "You are already registered");
		return true;
	}
	if (cmd.getTokens().size() < 2) {
		cli->sendReply("461", "Not enough parameters");
		return false;
	}
	if (cmd.getTokens().size() == 2) {
		if (cmd.getTokens()[1] == serv.getPassword()) {
			cli->sendReply("001", "Welcome to the Internet Relay Network " + cli->getNickname());
			return true;
		}
	}
	return false;
}