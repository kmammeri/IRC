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
# include "../Client/Client.hpp"
# include "../Channel/Channel.hpp"
# include "../Commands/ACommand.hpp"

using namespace std;

// IRCServer class
class IRCServer {
	private:
		int						_port;
		string					_password;
		
		int 					_mainSock;
		vector<struct pollfd>	_fds;

		map<int, Client>		_clients;
		map<string, Channel>	_channels;
		map<string, ACommand*>	_commands;

	public:
		IRCServer(int port, const char* password);
		void 	start();
		void 	setCmds();
		void 	acceptConnection();
		string	receiveMessage(int fd);
		void 	disconnectClient(int clientfd);
		void	sendToAll(string msg);
		void	parseMessage(int clientfd, string msg);
		void 	stop();
};