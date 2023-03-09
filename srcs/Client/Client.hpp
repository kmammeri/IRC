#pragma once

#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdexcept>
#include <iostream>
// #define SERVER_NAME "irc.42.fr"
#define SERVER_NAME "test"



using namespace std;

class Client {
	private:
		int		_fd;
		string	_username;
		string	_nickname;
		bool 	_isAuthentificated;
		bool	_isRegistered;

	public:
		Client(int fd);
		~Client();

		void 	sendReply(string const & code, string const & reply) const;

		// Setters
		void 	setUsername(string const & username);
		void 	setNickname(string const & nickname);
		void 	setAuthentification(bool auth);
		void	setRegistration(bool reg);

		// Getters
		int				getFd() const;
		string const &	getNickname() const;
		string const &	getUsername() const;
		bool			isAuthentificated() const;
		bool			isRegistered() const;
};