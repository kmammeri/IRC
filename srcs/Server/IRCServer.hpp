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
		void 	_setCmdsBank();
		void 	_acceptConnection();
		void 	_performCommand(Input const & input, Client *cli);
		void	_registrationProced() const;

		bool	_tryAuthentification(Input const & input, Client *cli, IRCServer & serv);
		bool	_tryRegistration(Input const & input, Client *cli, IRCServer & serv);

	public:
		IRCServer(int port, const char* password, int state);
		void 	start();
		string	receiveMessage(int fd);
		void 	disconnectClient(int clientfd);

		// Getters
		Client *		getClient(int fd);
		Client * 		getClient(string username);
		string const &	getPassword() const;

};