
#include "Commands.hpp"

bool USER::execute(Input const & cmd, Client * cli, IRCServer & serv) {
	cout << "USER::execute(:: " << cmd.getTokens().front() << " ::)" << "on client " << cli->getFd() << endl;
	(void)serv;
	return true;
}