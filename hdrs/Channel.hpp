#pragma once

#include <cstring>
#include <set>
#include <map>

#include "Client.hpp"

using namespace std;

class Channel {
	private:
		set<Client>		_usersInChannel;
	public:
		Channel(/* args */);
		~Channel();
};