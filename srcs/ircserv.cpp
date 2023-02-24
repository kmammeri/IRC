#include "../hdrs/ircserv.hpp"
#include "../hdrs/IRCServer.hpp"
#include "../hdrs/utils.hpp"


int main(int ac, char *av[]) {
	
	// Check number of arguments
	if (ac != 3) {
		cout << "Usage: ./ircserv <port> <password>" << endl;
		return 0;
	}

	// Check port
	string strport(av[1]);
	if (strport.find_first_not_of("0123456789") != string::npos) {
		cout	<< "Usage: ./ircserv <port> <password>" << endl
				<< "Port must be a number" << endl;
		return 0;
	}
	int port = atoi(av[1]);
	if (port < 0 || port > 65535) {
		cout	<< "Usage: ./ircserv <port> <password>" << endl
				<< "Port range required: [0...65535]" << endl;
		return 0;
	}

	// Create the server
	IRCServer ircserv(port, av[2]);

	// Start the server
	ircserv.start();
}