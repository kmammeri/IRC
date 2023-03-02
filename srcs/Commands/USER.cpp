
#include "Commands.hpp"

void USER::execute(int clientfd, string msg) {
	cout << "USER::execute(:: " << msg << " ::)" << "on client " << clientfd << endl;
	// do something
}