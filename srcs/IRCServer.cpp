#include "../hdrs/IRCServer.hpp"

// Constructor
IRCServer::IRCServer(int port,  const char* password):
	_port(port),
	_password(password) {}


void IRCServer::start() {
    // Create a socket
    bzero(this->_sockaddr.sin_zero, sizeof(this->_sockaddr.sin_zero));

    this->_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_sockfd < 0) {
        std::cerr << "Error: socket() failed" << std::endl;
        exit(1);
    }

	// Bind the socket to the port
    bind(this->_sockfd, (sockaddr *)&this->_sockaddr, sizeof(_sockaddr));
    
    // Listen for connections
    listen(this->_sockfd, 5);

	// Accept connections
    while (1) {
        int clientfd = accept(this->_sockfd, NULL, NULL);
        if (clientfd < 0) {
            std::cerr << "Error: accept() failed" << std::endl;
            exit(1);
        }
    }

    // ********la suite c'est copilot qui a mi mais je crois pas qu'on doit faire çadu multithreading
	// Create a new thread for each connection
	// Each thread will handle the connection
}