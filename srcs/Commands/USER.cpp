
#include "Commands.hpp"

void USER::execute(Input const & cmd, Client const & cli) {
	cout << "USER::execute(:: " << cmd.getCommand().front() << " ::)" << "on client " << cli.getFd() << endl;

	// do something
}