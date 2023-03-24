#pragma once

#include <iostream>
#include <string>

#include "../Client/Client.hpp"
#include "../Input/Input.hpp"
#include "../Server/IRCServer.hpp"

class Client;
class Input;
class IRCServer;

using namespace std;

class ACommand {
	public:
		virtual bool execute(Input const & cmd, Client * cli, IRCServer & serv) = 0;
};

class PASS: public ACommand {
	public:
		virtual bool execute(Input const & cmd, Client * cli, IRCServer & serv);
};

class USER: public ACommand {
	public:
		virtual bool	execute(Input const & cmd, Client * cli, IRCServer & serv);
};

class NICK: public ACommand {
	public:
		virtual bool	execute(Input const & cmd, Client * cli, IRCServer & serv);

};

class JOIN: public ACommand {
	public:
		virtual bool execute(Input const & cmd, Client * cli, IRCServer & serv);
};

class PRIVMSG: public ACommand {
	public:
		virtual bool execute(Input const & cmd, Client * cli, IRCServer & serv);
};

class KICK: public ACommand {
	public:
		virtual bool execute(Input const & cmd, Client * cli, IRCServer & serv);
};

class PING: public ACommand {
	public:
		virtual bool execute(Input const & cmd, Client * cli, IRCServer & serv);
};