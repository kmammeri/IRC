
#include "Commands.hpp"

void PASS::execute(int clientfd, string msg) {
	cout << "PASS::execute(:: " << msg << " ::)" << "on client " << clientfd << endl;
	// do something
}