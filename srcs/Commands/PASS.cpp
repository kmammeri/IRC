
#include "Commands.hpp"

void PASS::execute(Input const & cmd, Client const & cli) {
	cout << "PASS::execute(:: " << cmd.getCommand().front() << " ::)" << "on client " << cli.getFd() << endl;
	// do something
}