#include "Commands.hpp"

void JOIN::execute(Input const & cmd, Client const & cli) {
	cout << "JOIN::execute(:: " << cmd.getCommand().front() << " ::)" << "on client " << cli.getFd() << endl;

	// do something
}