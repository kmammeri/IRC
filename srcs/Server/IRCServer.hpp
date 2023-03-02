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
# include <arpa/inet.h>
# include <fcntl.h>
# include <unistd.h>


# include "../Client/Client.hpp"
# include "../Channel/Channel.hpp"
# include "../Commands/Commands.hpp"

using namespace std;

class Channel;
class Client;
class ACommand;

class IRCServer {
	private:
		int						_port;
		string					_password;
		int 					_state;				
		
		int 					_mainSock;
		vector<struct pollfd>	_pollfds;

		vector<Client>			_clients;
		map<string, Channel>	_channels;
		map<string, ACommand*>	_commands;

		void 	_init();
		void 	_setCmds();
		void 	_acceptConnection();

	public:
		IRCServer(int port, const char* password, int state);
		void 	start();
		void 	authentification(int clientfd);
		string	receiveMessage(int fd);
		void 	disconnectClient(int clientfd);
		void	sendToAll(string msg);
		void	parseMessage(int clientfd, string msg);
		void 	stop();

		// Getters

		vector<Client>::const_iterator	getClient(int fd) const;
		vector<Client>::const_iterator	getClient(string username) const;
};