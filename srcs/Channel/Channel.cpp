#include "Channel.hpp"

Channel::Channel(string name, int mode):
	_name(name),
	_mode(mode) {}

Channel::~Channel() {}

// Getters
string	Channel::getName() const {
	return this->_name;
}

string	Channel::getTopic() const {
	return this->_topic;
}

int		Channel::getMode() const {
	return this->_mode;
}

void	Channel::addUser(Client * cli) {
	if (this->_users.find(cli->getNickname()) == this->_users.end())
		this->_users.insert(pair<string, Client>(cli->getNickname(), *cli));
}