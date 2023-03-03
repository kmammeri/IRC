#pragma once

#include <iostream>
#include <string>

#include "../Client/Client.hpp"
#include "../Input/Input.hpp"

class Client;
class Input;

using namespace std;

class ACommand {
	public:
		virtual void execute(Input const & cmd, Client const &) = 0;
};

class PASS: public ACommand {
	public:
		virtual void execute(Input const & cmd, Client const &);
};

class USER: public ACommand {
	public:
		virtual void execute(Input const & cmd, Client const &);
};

class NICK: public ACommand {
	public:
		virtual void execute(Input const & cmd, Client const &);
};

class JOIN: public ACommand {
	public:
		virtual void execute(Input const & cmd, Client const &);
};