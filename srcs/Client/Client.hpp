#pragma once

#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdexcept>
#include <iostream>
#include "../ircserv.hpp"



using namespace std;

class Client {
	private:
		int		_fd;
		string	_username;
		string	_nickname;
		string 	_realname;
		string	_hostname;
		string	_servername;
		bool 	_isAuthentificated;
		bool	_isRegistered;


	public:
		Client(int fd, string const & hostname);
		~Client();

		void 	sendReply(string reply) const;

		// Setters
		void 	setUsername(string const & username);
		void 	setNickname(string const & nickname);
		void 	setRealname(string const & realname);
		void 	setServername(string const & servername);
		void 	setAuthentification(bool auth);
		void	setRegistration(bool reg);

		// Getters
		int				getFd() const;
		string const &	getNickname() const;
		string const &	getUsername() const;
		bool			isAuthentificated() const;
		bool			isRegistered() const;
		string const & 	getRealname() const;
		string const & 	getHostname() const;
		string const & 	getServername() const;
};