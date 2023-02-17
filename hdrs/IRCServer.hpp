#pragma once
# include <string>
# include <iostream>

using namespace std;

// IRCServer class
class IRCServer {
	public:
		IRCServer(int port, const char* password);
		void start();
	
	private:
		int		 _port;
		string _password;
};	