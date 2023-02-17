#include "../hdrs/IRCServer.hpp"

// Constructor
IRCServer::IRCServer(int port,  const char* password):
    _port(port), 
    _password(password) {}


void IRCServer::start() {
    // Create a socket
    // Bind the socket to the port
    // Listen for connections
    // Accept connections
    // Create a new thread for each connection
    // Each thread will handle the connection
}