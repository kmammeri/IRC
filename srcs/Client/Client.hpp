#pragma once

#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdexcept>
#include <iostream>


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

		void 	sendReply(string const & code, string const & reply) const;

		// Setters
		void 	setUsername(string const & username);
		void 	setNickname(string const & nickname);
		void 	setAuthentification(bool isAuth);

		// Getters
		int				getFd() const;
		string const &	getNickname() const;
		string const &	getUsername() const;
		bool			isAuthentificated() const;
};