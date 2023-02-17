#include "../hdrs/IRCServer.hpp"

int main(int ac, char *av[]) {
    
    // Check the number of arguments
    if (av[3] || !av[2]){
        std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
        return 0;
    }
    // Create the server
    IRCServer ircserv(ac, av[1]);
    // ...
    // Start the server
    ircserv.start();
    // ...
}