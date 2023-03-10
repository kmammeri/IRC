#include "IRCServer.hpp"
#include "../ircserv.hpp"
#include "../Commands/Commands.hpp"
#include "../Input/Input.hpp"
#include "../Client/Client.hpp"

// Constructors

IRCServer::IRCServer(int port,  const char* password, int state):
	_port(port),
	_password(password), 
	_state(state)
	 {
		this->_serverName = SERVER_NAME;
		std::time_t result = std::time(NULL);
    	this->_creationDate = std::ctime(&result);
	 }

// Memnber functions

void IRCServer::_init() {

	// Create a socket
	this->_mainSock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_mainSock < 0)
		throw runtime_error("Error: socket() failed");
	this->_pollfds.push_back((struct pollfd){this->_mainSock, POLLIN, 0});

	// Configure the socket
	struct sockaddr_in _sockaddr;
	_sockaddr.sin_family = AF_INET;							// host byte order
	_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);			// automatically fill with my IP address
	_sockaddr.sin_port = htons(this->_port);				// short, network byte order
	bzero(_sockaddr.sin_zero, sizeof(_sockaddr.sin_zero));	// zero the rest of the struct
	
	// Bind the socket to the port
	if (bind(this->_mainSock, (struct sockaddr *)&_sockaddr, sizeof(_sockaddr)) < 0)
		throw runtime_error("Error: bind() failed");
	
	// Listen for connections
	if (listen(this->_mainSock, QUEUE_MAX) < 0)
		throw runtime_error("Error: listen() failed");

	// Set the socket to non-blocking
	fcntl(this->_mainSock, F_SETFL, O_NONBLOCK);
}

void IRCServer::_setCmdsBank() {
	this->_commands.insert(pair<string, ACommand*>("PASS", new PASS()));
	this->_commands.insert(pair<string, ACommand*>("USER", new USER()));
	this->_commands.insert(pair<string, ACommand*>("NICK", new NICK()));
	this->_commands.insert(pair<string, ACommand*>("JOIN", new JOIN()));
	// this->_commands.insert(pair<string, ACommand*>("PART", new PART()));
	this->_commands.insert(pair<string, ACommand*>("PRIVMSG", new PRIVMSG()));
	// this->_commands.insert(pair<string, ACommand*>("QUIT", new QUIT()));
	// this->_commands.insert(pair<string, ACommand*>("PING", new PING()));
	// this->_commands.insert(pair<string, ACommand*>("PONG", new PONG()));
	// this->_commands.insert(pair<string, ACommand*>("LIST", new LIST()));
	// this->_commands.insert(pair<string, ACommand*>("NAMES", new NAMES()));
	// this->_commands.insert(pair<string, ACommand*>("TOPIC", new TOPIC()));
	// this->_commands.insert(pair<string, ACommand*>("MODE", new MODE()));
	// this->_commands.insert(pair<string, ACommand*>("KICK", new KICK()));
	// this->_commands.insert(pair<string, ACommand*>("INVITE", new INVITE()));
	// this->_commands.insert(pair<string, ACommand*>("NOTICE", new NOTICE()));
}

void IRCServer::start() {

	this->_init();
	this->_setCmdsBank();

	while (this->_state == UP) {
		// Wait for a activity on one of the sockets
		poll(this->_pollfds.data(), this->_pollfds.size(), -1);

		// When something happened on the main socket, then it's an incoming connection
		// else it's a message from a client
		for (size_t i = 0; i < this->_pollfds.size(); i++) {
			if (this->_pollfds[i].revents & POLLIN) {
				if (this->_pollfds[i].fd == this->_mainSock) {
					try	{
						this->_acceptConnection();
					}
					catch(const exception& e) {
						cerr << e.what() << endl;
					}
				}
				else {
					try {

						// get Client and check if there is a client corresponding to pollfd in vector
						Client *client = getClient(this->_pollfds[i].fd);
						if (client == NULL)
							throw runtime_error("Error: Client not found in vector");

						// tokenise and check if message of client is empty
						Input input(receiveMessage(this->_pollfds[i].fd));
						input.printTokens();
						if (input.empty()) {
							cout << "Empty input" << endl;
							continue;
						}
						_performCommand(input, client);
					}
					catch(const exception& e) {
						cerr << e.what();
					}
				}
			}
		}
		cout << "all channels:::" << endl;
		for (map<string, Channel *>::iterator it = this->_channels.begin(); it != this->_channels.end(); ++it){
			cout << "  " << it->first << ":" << endl;
			for (map<string, Client>::const_iterator it2 = it->second->getUsers().begin(); it2 != it->second->getUsers().end(); ++it2) {
				cout << "    " << it2->first << endl;
			}
		}
		cout << "========================================" << endl;
	}
}

// Create a new unauthentificate client and add it to the clients vector and pollfds vector
void IRCServer::_acceptConnection() {
	struct sockaddr_in clientaddr;
	socklen_t clientlen = sizeof(clientaddr);
	int clientfd = accept(this->_mainSock, (struct sockaddr *)&clientaddr, &clientlen);
	if (clientfd < 0) {
		throw runtime_error("Error: accept() failed\n");
	}
	else {
		fcntl(clientfd, F_SETFL, O_NONBLOCK);
		Client client(clientfd, inet_ntoa(clientaddr.sin_addr));
		this->_pollfds.push_back((struct pollfd){clientfd, POLLIN, 0});
		this->_clients.push_back(client);
		cout << "New connection on SERV on socketfd: " << clientfd << endl;
	}
}

void IRCServer::_registrationProced(Client * cli) const {

	cout << "LE CLIENT EST REGISTER" << endl;
	// cli->sendReply("001 Welcome to the Internet Relay Network " + cli->getNickname() + "!" + cli->getUsername() + "@" + "localhost\n"); /*or cli->getHostname() instead of localhost -> IP of the client*/
	// cli->sendReply("002 Your host is " + this->_serverName + ", running version 1.0\n");
	// cli->sendReply("003 This server was created " + this->_creationDate);
	// cli->sendReply("004 " + this->_serverName + "version 1.0, usermodes=OPERATOR-REGISTERED, channelmodes=PUBLIC-PRIVATE-INVITE_ONLY-PRIVATE_WITH_INVITE\n");
	// // cli->sendReply("005 " + "1 :is supported by this server\n");
	// cli->sendReply("005 PREFIX=(ov)@+ CHANMODES=beI,k,l,imnpstrRcOAQKVCuzNSMTGZ NETWORK=IRCNetare supported by this server\n");
	cli->setRegistration(true);


	// cli->sendReply("001 " + cli->getNickname() + " :Welcome to the Internet Relay Network " + cli->getNickname() + "!" +
        //    cli->getUsername() + "@" + cli->getHostname() + "\r\n");

	cli->sendReply(":" + string(SERVER_NAME) + " 001 " + cli->getNickname() + " :Welcome to the Internet Relay Network " + cli->getNickname() + "!" +
            cli->getUsername() + "@" + cli->getHostname() + "\r\n");
}

void IRCServer::_performCommand(Input const & input, Client *cli) {

	if (cli->isRegistered() == false && !(input.getTokens().front() == "PASS" || input.getTokens().front() == "USER" || input.getTokens().front() == "NICK" || input.getTokens().front() == "CAP")) {
		cout << "Error: You must be authentificated first" << endl;
		disconnectClient(cli->getFd());
		return ;
	}
	if (this->_commands.find(input.getTokens().front()) == this->_commands.end()) {
		if (input.getTokens().front() != "MODE")
		{
			cout << "Error: Command not found in map of commands" << endl;
		}
		return ;
	}
	this->_commands[input.getTokens().front()]->execute(input, cli, *this);
	if (cli->isRegistered() == false) {
		if (cli->getNickname() != "" && cli->getUsername() != "" && cli->isAuthentificated() == true) {
			_registrationProced(cli);
		}
	}
}

void IRCServer::disconnectClient(int clientfd) {
	close(clientfd);
	for (size_t i = 0; i < this->_clients.size(); i++) {
		if (this->_clients[i].getFd() == clientfd) {
			this->_clients.erase(this->_clients.begin() + i);
			break;
		}
	}
	for (size_t i = 0; i < this->_pollfds.size(); i++) {
		if (this->_pollfds[i].fd == clientfd) {
			this->_pollfds.erase(this->_pollfds.begin() + i);
			break;
		}
	}
	cout << "Client " << clientfd << " disconnected" << endl;
}

string IRCServer::receiveMessage(int clientfd) {
	char buffer[LEN_MAX];
	int n = recv(clientfd, buffer, sizeof(buffer), 0);
	if (n < 0) {
		throw runtime_error("Error: recv() failed");
	}
	else if (n == 0) {
		disconnectClient(clientfd);
	}
	else {
		buffer[n] = '\0';
	}
	cout << "Received raw message from client " << clientfd << ": " << buffer << endl;
	return string(buffer);
}

// Getters

Client * IRCServer::getClient(int fd) {
	for (vector<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->getFd() == fd) {
			return (&(*it));
		}
	}
	return NULL;
}

Client * IRCServer::getClientByUser(string username) {
	for (vector<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->getUsername() == username) {
			return (&(*it));
		}
	}
	return NULL;
}


Client * IRCServer::getClientByNick(string nickname) {
	for (vector<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->getNickname() == nickname) {
			return (&(*it));
		}
	}
	return NULL;
}

Channel * IRCServer::getChannel(string channelName) {
	if (this->_channels.find(channelName) == this->_channels.end())
		return NULL;
	return (this->_channels[channelName]);
}

string const & IRCServer::getPassword() const {
	return this->_password;
}

// Setters

void IRCServer::createChannel(string const & channelName) {
	Channel * newChan = new Channel(channelName, PUBLIC);
	this->_channels.insert(std::pair<string, Channel *>(channelName, newChan));
}