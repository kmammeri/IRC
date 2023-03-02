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