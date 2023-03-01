#pragma once

#include <cstring>
#include <set>
#include <map>

#include "Client.hpp"

enum ChannelMode {
	PUBLIC = 0,
	PRIVATE = 1,
	INVITE_ONLY = 2,
	PRIVATE_WITH_INVITE = 3,
};

using namespace std;

class Channel {
	private:
		string				_name;
		string				_topic;
		int					_mode;
		set<Client>			_usersInChannel;
		set<Client>			_operatorsInChannel;
		set<Client>			_inviteList;
		
	public:
		Channel(/* args */);
		~Channel();
};