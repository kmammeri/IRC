#include "../../hdrs/Commands/JoinCmd.hpp"

void JoinCmd::execute(int clientfd, string msg) {
	cout << "JoinCmd::execute(:: " << msg << " ::)" << "on client " << clientfd << endl;
	// do something
}