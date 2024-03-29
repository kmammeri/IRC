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
# include <ctime>
# include <csignal>

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
		string					_serverName;			
		int 					_mainSock;
		vector<struct pollfd>	_pollfds;

		vector<Client>			_clients;
		map<string, Channel *>	_channels;
		map<string, ACommand *>	_commands;

		void 	_init();
		void 	_setCmdsBank();
		void 	_acceptConnection();
		void 	_performCommand(Input const & input, Client *cli);
		void	_registrationProced(Client * cli) const;

		bool	_tryAuthentification(Input const & input, Client *cli, IRCServer & serv);
		bool	_tryRegistration(Input const & input, Client *cli, IRCServer & serv);

	public:
		IRCServer(int port, const char* password);
		~IRCServer();
		void 	start();
		string	receiveMessage(int fd);
		void 	disconnectClient(int clientfd);

		// Getters
		bool 			usernameAlreadyExists(string const & username);
		bool 			nicknameAlreadyExists(string const & nickname);
		bool 			channelAlreadyExists(string const & channelName);

		Client *		getClient(int fd);
		Client *		getClientByUser(string username);
		Client *		getClientByNick(string username);
		Channel *		getChannel(string channelName);
		vector<string>	getVectChannels() const;
		map<string, Channel *>	getChannels();


		string const &	getPassword() const;

		// Setters
		void 			createChannel(string const & channelName, const int &mode);
		void 			deleteChannel(string const & channelName);

};