#pragma once

#include <string>

using namespace std;

class Client {
	private:
		int		_fd;
		string	_username;
		string	_nickname;
		bool 	_isAuthentificated;

	public:
		Client(int fd, bool isAuth);
		~Client();

		int		getFd() const;
		string	getNickname() const;
		string	getUsername() const;
		bool	isAuthentificated() const;
};