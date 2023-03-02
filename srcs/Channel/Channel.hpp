#pragma once

#include <cstring>
#include <vector>
#include <map>

#include "../Client/Client.hpp"

using namespace std;

class Client;

class Channel {
	private:
		string				_name;
		string				_topic;
		int					_mode;
		map<string, Client>	_users;
		map<string, Client>	_operators;
		map<string, Client>	_inviteList;
		
	public:
		Channel(string name, int mode);
		~Channel();

		// Getters
		string	getName() const;
		string	getTopic() const;
		int		getMode() const;
};