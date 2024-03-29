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

string const &	Channel::getOperator() const {
	return this->_operator;
}

void	Channel::addUser(Client * cli) {
	if (this->_users.find(cli->getNickname()) == this->_users.end())
		this->_users.insert(pair<string, Client>(cli->getNickname(), *cli));
}

void	Channel::addInvite(Client * cli) {
	if (this->_inviteList.find(cli->getNickname()) == this->_inviteList.end())
		this->_inviteList.insert(pair<string, Client>(cli->getNickname(), *cli));
}

string Channel::getStrAllUsers() const {
	string clients;

    for (map<string, Client>::const_iterator it = this->_users.begin(); it != this->_users.end(); ++it) {
        if (it->second.getNickname() == this->_operator)
            clients += "@";
        clients += it->second.getNickname();
		if (this->_users.size() > 1)
			if (it != --this->_users.end())
				clients += " ";
    }
    return clients;;
}

string Channel::getStrAllInvite() const {
	string clients;

    for (map<string, Client>::const_iterator it = this->_inviteList.begin(); it != this->_inviteList.end(); ++it) {
        if (it->second.getNickname() == this->_operator)
            clients += "@";
        clients += it->second.getNickname();
		if (this->_inviteList.size() > 1)
			if (it != --this->_inviteList.end())
				clients += " ";
    }
    return clients;;
}

void Channel::sendToAll(string msg) const {
	for (map<string, Client>::const_iterator it = this->_users.begin(); it != this->_users.end(); ++it) {
		it->second.sendReply(msg);
	}
}

void Channel::sendToAllOthers(string msg, const string &cli) const {
	for (map<string, Client>::const_iterator it = this->_users.begin(); it != this->_users.end(); ++it) {
		if (it->second.getNickname() != cli)
			it->second.sendReply(msg);
	}
}

map<string, Client> const &	Channel::getUsers() const {
	return this->_users;
}

map<string, Client> const &	Channel::getInviteListe() const {
	return this->_inviteList;
}

void	Channel::setOperator(string const & op) {
	this->_operator = op;
}

void Channel::removeUser(Client *cli)
{
	
	if (this->_users.find(cli->getNickname()) != this->_users.end())
	{
		this->_users.erase(cli->getNickname());
	}
}

void Channel::removeInvite(Client *cli)
{
	
	if (this->_inviteList.find(cli->getNickname()) != this->_inviteList.end())
	{
		this->_inviteList.erase(cli->getNickname());
	}
}

void Channel::setTopic(string const & topic) {
	this->_topic = topic;
}

string Channel::getFirstUser() const {
	return this->_users.begin()->second.getNickname();
}