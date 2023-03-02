
#include "Commands.hpp"

void NICK::execute(int clientfd, string msg) {
	cout << "NICK::execute(:: " << msg << " ::)" << "on client " << clientfd << endl;
	// do something
}