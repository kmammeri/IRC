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
		string				_operator;
		int					_mode;
		map<string, Client>	_users;
		map<string, Client>	_inviteList;
		
	public:
		Channel(string name, int mode);
		~Channel();

		void sendToAll(string msg) const;
		void sendToAllOthers(string msg, const string &cli) const;

		// Getters
		string	getName() const;
		string	getTopic() const;
		int		getMode() const;
		string const &	getOperator() const;

		map<string, Client> const &	getUsers() const;
		map<string, Client> const &	getInviteListe() const;
		void	addUser(Client * cli);
		void	addInvite(Client * cli);
		void	removeUser(Client * cli);
		void	removeInvite(Client * cli);
		string	getStrAllUsers() const;
		string	getStrAllInvite() const;
		string	getFirstUser() const;
		void	setOperator(string const & op);
		void	setTopic(string const & topic);

};