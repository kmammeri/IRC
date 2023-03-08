#include "Commands.hpp"

bool JOIN::execute(Input const & cmd, Client * cli, IRCServer & serv) {
	cout << "JOIN::execute(:: " << cmd.getTokens().front() << " ::)" << "on client " << cli->getFd() << endl;
	(void)serv;
	return true;
	// do something
}