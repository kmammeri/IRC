#pragma once
# include <string>
# include <iostream>
# include <sys/socket.h>
# include <cstdlib>
# include <map>

using namespace std;

// IRCServer class
class IRCServer {
	public:
		IRCServer(int port, const char* password);
		void start();
	
	private:
		int			_port;
		string		_password;

		int 		_sockfd;
		sockaddr 	*_addr;
		// sockaddr looks like:
		// struct sockaddr {
        //        sa_family_t sa_family;
        //        char        sa_data[14];
		// }
};
