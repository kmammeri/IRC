#include "../hdrs/IRCServer.hpp"

// Constructor
IRCServer::IRCServer(int port,  const char* password):
	_port(port),
	_password(password) {}


void IRCServer::start() {
    // Create a socket
    this->_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_sockfd < 0) {
        std::cerr << "Error: socket() failed" << std::endl;
        exit(1);
    }


    bzero(this->_sockaddr.sin_zero, sizeof(this->_sockaddr.sin_zero));
    this->_sockaddr.sin_family = AF_INET;
    this->_sockaddr.sin_port = htons(this->_port);
    this->_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    

	// Bind the socket to the port
    if (bind(this->_sockfd, (struct sockaddr *)&this->_sockaddr, sizeof(this->_sockaddr)) < 0) {
        std::cerr << "Error: bind() failed" << std::endl;
        exit(1);
    }
    
    // Listen for connections
    if (listen(this->_sockfd, 5) < 0) {
        std::cerr << "Error: listen() failed" << std::endl;
        exit(1);
    }

	// Accept connections
    while (1) {
        int clientfd = accept(this->_sockfd, NULL, NULL);
        if (clientfd < 0) {
            std::cerr << "Error: accept() failed" << std::endl;
            exit(1);
        }
        else {
            std::cout << "New connection on  SERV fd: " << this->_sockfd << "at CLI fd:" << clientfd << std::endl;
        }
    }

    // ********la suite c'est copilot qui a mi mais je crois pas qu'on doit faire çadu multithreading
	// Create a new thread for each connection
	// Each thread will handle the connection
}