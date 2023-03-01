#pragma once

#include <string>

using namespace std;

class Client {
	private:
		int		_sockfd;
		string	_nickname;
		string	_username;
	
	public:
		Client(int sockfd);
		~Client();
};