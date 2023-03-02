
#include "IRCServer.hpp"
#include "../ircserv.hpp"
#include "../Commands/Commands.hpp"
#include "../Input/Input.hpp"

IRCServer::IRCServer(int port,  const char* password, int state):
	_port(port),
	_password(password), 
	_state(state) {}


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

void IRCServer::_setCmds() {
	this->_commands.insert(pair<string, ACommand*>("PASS", new PASS()));
	this->_commands.insert(pair<string, ACommand*>("USER", new USER()));
	this->_commands.insert(pair<string, ACommand*>("NICK", new NICK()));
	this->_commands.insert(pair<string, ACommand*>("JOIN", new JOIN()));
	// this->_commands.insert(pair<string, ACommand*>("PART", new PART()));
	// this->_commands.insert(pair<string, ACommand*>("PRIVMSG", new PRIVMSG()));
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
	this->_setCmds();

	while (this->_state == UP) {
		// Wait for a activity on one of the sockets
		poll(this->_pollfds.data(), this->_pollfds.size(), -1);

		// If something happened on the main socket, then it's an incoming connection
		// else it's a message from a client
		for (size_t i = 0; i < this->_pollfds.size(); i++) {
			if (this->_pollfds[i].revents & POLLIN) {
				if (this->_pollfds[i].fd == this->_mainSock) {
					try	{
						this->_acceptConnection();
						cout << "New connection on SERV" << endl;
					}
					catch(const exception& e) {
						cerr << e.what() << endl;
					}
				}
				else {
					try {
						Input input(receiveMessage(this->_pollfds[i].fd));
						input.parse();
					}
					catch(const exception& e) {
						cerr << e.what() << endl;
					}
				}
			}
		}
	}
}

void IRCServer::_acceptConnection() {
	struct sockaddr_in clientaddr;
	socklen_t clientlen = sizeof(clientaddr);
	int clientfd = accept(this->_mainSock, (struct sockaddr *)&clientaddr, &clientlen);
	if (clientfd < 0) {
		throw runtime_error("Error: accept() failed");
	}
	else {
		fcntl(clientfd, F_SETFL, O_NONBLOCK);
		Client client(clientfd, false);
		this->_pollfds.push_back((struct pollfd){clientfd, POLLIN, 0});
		this->_clients.push_back(client);
	}
}

string IRCServer::receiveMessage(int clientfd) {
	char buffer[LEN_MAX];
	int n = recv(clientfd, buffer, sizeof(buffer), 0);
	if (n < 0) {
		throw runtime_error("Error: recv() failed");
	}
	else if (n == 0) {
		cout << "Client " << clientfd << " disconnected" << endl;
		disconnectClient(clientfd);
	}
	else {
		buffer[n] = '\0';
		cout << "Message received from " << clientfd << ": " << buffer << endl;
	}
	return string(buffer);
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
}

void IRCServer::stop() {
	close(this->_mainSock);
}


// Getters
vector<Client>::const_iterator IRCServer::getClient(int fd) const {
	for (vector<Client>::const_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->getFd() == fd) {
			return it;
		}
	}
	return this->_clients.end();
}

vector<Client>::const_iterator IRCServer::getClient(string username) const {
	for (vector<Client>::const_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->getUsername() == username) {
			return it;
		}
	}
	return this->_clients.end();
}