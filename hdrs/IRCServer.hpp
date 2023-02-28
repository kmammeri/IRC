#pragma once
# include <string>
# include <cstring>
# include <cerrno>
# include <iostream>
# include <sys/socket.h>
# include <netinet/in.h> 
# include <cstdlib>
# include <map>
# include <strings.h>
# include <poll.h>
# include <vector>
# include <set>
# include <arpa/inet.h>
# include <fcntl.h>
# include <unistd.h>
# include "../hdrs/Client.hpp"
# include "../hdrs/Channel.hpp"

using namespace std;

// IRCServer class
class IRCServer {
	private:
		int						_port;
		string					_password;
		
		int 					_mainSock;
		map<int, Client>		_clients;
		vector<struct pollfd>	_fds;

		set<Channel>			_channels;

	public:
		IRCServer(int port, const char* password);
		void start();
		void acceptConnection();
		void receiveMessage(int fd);
		void disconnectClient(int clientfd);
};