
#include "../hdrs/IRCServer.hpp"
#include "../hdrs/ircserv.hpp"

// Constructor
IRCServer::IRCServer(int port,  const char* password):
	_port(port),
	_password(password) {}


void IRCServer::start() {

	// Create a socket
	this->_mainSock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_mainSock < 0) {
		std::cerr << "Error: socket() failed" << std::endl;
		exit (EXIT_FAILURE);
	}
	this->_fds.push_back((struct pollfd){this->_mainSock, POLLIN, 0});

	// Bind the socket to the port
	struct sockaddr_in _sockaddr;
	_sockaddr.sin_family = AF_INET;							// host byte order
	_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);			// automatically fill with my IP address
	// _sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// if (_sockaddr.sin_addr.s_addr == INADDR_NONE) {
	// 	std::cerr << "Error: inet_addr() failed" << std::endl;
	// 	exit (EXIT_FAILURE);
	// }
	_sockaddr.sin_port = htons(this->_port);				// short, network byte order
	bzero(_sockaddr.sin_zero, sizeof(_sockaddr.sin_zero));	// zero the rest of the struct
	if (bind(this->_mainSock, (struct sockaddr *)&_sockaddr, sizeof(_sockaddr)) < 0) {
		std::cerr << "Error: bind() failed" << std::endl;
		exit (EXIT_FAILURE);
	}
	
	// Listen for connections
	if (listen(this->_mainSock, 5) < 0) {
		std::cerr << "Error: listen() failed" << std::endl;
		exit(EXIT_FAILURE);
	}


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
						std::cout << "New connection on SERV" << std::endl;
					}
					catch(const std::exception& e) {
						std::cerr << e.what() << '\n';
					}
					
				}
				else {
					cout << "onbest la" << std::endl;
					try {
						receiveMessage(this->_fds[i].fd);
					}
					catch(const std::exception& e) {
						std::cerr << e.what() << '\n';
					}
				}
			}
		}
	}
}

void IRCServer::receiveMessage(int clientfd) {
	char buffer[512];
	int n = recv(clientfd, buffer, sizeof(buffer), 0);
	if (n < 0) {
		throw std::runtime_error("Error: recv() failed");
	}
	else if (n == 0) {
		close(clientfd);
		this->_clients.erase(clientfd);
	}
	else {
		buffer[n] = '\0';
		std::cout << "Message received from " << clientfd << ": " << buffer << std::endl;
	}
}

void IRCServer::acceptConnection() {
	struct sockaddr_in clientaddr;
	socklen_t clientlen = sizeof(clientaddr);
	int clientfd = accept(this->_mainSock, (struct sockaddr *)&clientaddr, &clientlen);
	if (clientfd < 0) {
		throw std::runtime_error("Error: accept() failed");
	}
	else {
		fcntl(clientfd, F_SETFL, O_NONBLOCK);
		Client client(clientfd);
		this->_clients.insert(std::pair<int, Client>(clientfd, client));
		this->_fds.push_back((struct pollfd){clientfd, POLLIN, 0});
	}
}