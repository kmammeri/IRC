
#include "IRCServer.hpp"
#include "../ircserv.hpp"
#include "../Commands/JoinCmd.hpp"

// Constructor
IRCServer::IRCServer(int port,  const char* password):
	_port(port),
	_password(password) {}


void IRCServer::start() {

	// Create a socket
	this->_mainSock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_mainSock < 0)
		throw runtime_error("Error: socket() failed");
	this->_fds.push_back((struct pollfd){this->_mainSock, POLLIN, 0});

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

	while (true) {
		// Wait for a activity on one of the sockets
		poll(this->_fds.data(), this->_fds.size(), -1);

		// If something happened on the main socket, then it's an incoming connection
		// else it's a message from a client
		for (size_t i = 0; i < this->_fds.size(); i++) {
			if (this->_fds[i].revents & POLLIN) {
				if (this->_fds[i].fd == this->_mainSock) {
					try	{
						acceptConnection();
						cout << "New connection on SERV" << endl;
					}
					catch(const exception& e) {
						cerr << e.what() << endl;
					}
				}
				else {
					try {
						parseMessage(this->_fds[i].fd, receiveMessage(this->_fds[i].fd));
					}
					catch(const exception& e) {
						cerr << e.what() << endl;
					}
				}
			}
		}
		// try
		// {
		// 	this->sendToAll("le message est nulll");
		// }
		// catch(const exception& e)
		// {
		// 	cerr << e.what() << endl;
		// }
		
	}
}

void IRCServer::parseMessage(int clientfd, string msg) {
	(void) clientfd;
	(void) msg;
	// this->_commands.find(msg.substr(0, msg.find(" ")))->second->execute(clientfd, msg);

	cout << msg << endl;
	cout << (msg == "JOIN\n") << endl;

	if (this->_commands.find(msg) != this->_commands.end()) {
		this->_commands.find(msg)->second->execute(clientfd, msg);
	}
	else {
		cout << "Command not found" << endl;
	}
}

void IRCServer::setCmds() {
	// this->_commands.insert(pair<string, ACommand*>("NICK", new NickCmd()));
	// this->_commands.insert(pair<string, ACommand*>("USER", new UserCmd()));
	this->_commands.insert(pair<string, ACommand*>("JOIN\n", new JoinCmd()));
	// this->_commands.insert(pair<string, ACommand*>("PART", new PartCmd()));
	// this->_commands.insert(pair<string, ACommand*>("PRIVMSG", new PrivmsgCmd()));
								// this->_commands.insert(pair<string, ACommand*>("QUIT", new QuitCmd()));
								// this->_commands.insert(pair<string, ACommand*>("PING", new PingCmd()));
								// this->_commands.insert(pair<string, ACommand*>("PONG", new PongCmd()));
	// this->_commands.insert(pair<string, ACommand*>("LIST", new ListCmd()));
	// this->_commands.insert(pair<string, ACommand*>("NAMES", new NamesCmd()));
	// this->_commands.insert(pair<string, ACommand*>("TOPIC", new TopicCmd()));
	// this->_commands.insert(pair<string, ACommand*>("MODE", new ModeCmd()));
	// this->_commands.insert(pair<string, ACommand*>("KICK", new KickCmd()));
	// this->_commands.insert(pair<string, ACommand*>("INVITE", new InviteCmd()));
	// this->_commands.insert(pair<string, ACommand*>("PASS", new PassCmd()));
	// this->_commands.insert(pair<string, ACommand*>("NOTICE", new NoticeCmd()));
}

void IRCServer::acceptConnection() {
	struct sockaddr_in clientaddr;
	socklen_t clientlen = sizeof(clientaddr);
	int clientfd = accept(this->_mainSock, (struct sockaddr *)&clientaddr, &clientlen);
	if (clientfd < 0) {
		throw runtime_error("Error: accept() failed");
	}
	else {
		fcntl(clientfd, F_SETFL, O_NONBLOCK);
		Client client(clientfd);
		this->_clients.insert(pair<int, Client>(clientfd, client));
		this->_fds.push_back((struct pollfd){clientfd, POLLIN, 0});
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
	this->_clients.erase(clientfd);
	for (size_t i = 0; i < this->_fds.size(); i++) {
		if (this->_fds[i].fd == clientfd) {
			this->_fds.erase(this->_fds.begin() + i);
			break;
		}
	}
}

void IRCServer::sendToAll(string msg) {
	for (map<int, Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (send(it->first, msg.c_str(), msg.length(), 0) < 0) {
			throw runtime_error("Error: send() failed");
		}
	}
}

void IRCServer::stop() {
	close(this->_mainSock);
}