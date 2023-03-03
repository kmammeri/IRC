
#include "Commands.hpp"

void NICK::execute(Input const & cmd, Client const & cli) {
	cout << "NICK::execute(:: " << cmd.getCommand().front() << " ::)" << "on client " << cli.getFd() << endl;

	// do something
}