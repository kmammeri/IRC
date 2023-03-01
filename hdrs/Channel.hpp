#pragma once

#include <cstring>
#include <set>
#include <map>

#include "Client.hpp"

using namespace std;

class Channel {
	private:
		string				_name;
		string				_topic;
		int					_mode;
		set<Client>			_users;
		set<Client>			_operators;
		set<Client>			_inviteList;
		
	public:
		Channel(string name, int mode);
		~Channel();
};