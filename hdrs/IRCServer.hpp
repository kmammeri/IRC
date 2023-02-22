#pragma once
# include <string>
# include <iostream>
# include <sys/socket.h>
# include <netinet/in.h>
# include <cstdlib>
# include <map>
# include <strings.h>

using namespace std;

// IRCServer class
class IRCServer {
	public:
		IRCServer(int port, const char* password);
		void start();
	
	private:
		int			_port;
		string		_password;

		int 				_sockfd;
		struct sockaddr_in 	_sockaddr;
};
