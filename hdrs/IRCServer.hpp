#include <string>
#include <iostream>

// IRCServer class
class IRCServer {
    public:
        IRCServer(int port, const char* password);
        void start();
    
    private:
        int         _port;
        std::string _password;
};