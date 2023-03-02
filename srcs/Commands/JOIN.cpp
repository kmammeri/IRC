#include "Commands.hpp"

void JOIN::execute(int clientfd, string msg) {
	cout << "JOIN::execute(:: " << msg << " ::)" << "on client " << clientfd << endl;
	// do something
}