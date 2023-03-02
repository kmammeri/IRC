#pragma once

#include <iostream>
#include <string>

using namespace std;

class ACommand {
	public:
		virtual void execute(int clientfd, string msg) = 0;
};

class PASS: public ACommand {
	public:
		virtual void execute(int clientfd, string msg);
};

class USER: public ACommand {
	public:
		virtual void execute(int clientfd, string msg);
};

class NICK: public ACommand {
	public:
		virtual void execute(int clientfd, string msg);
};

class JOIN: public ACommand {
	public:
		virtual void execute(int clientfd, string msg);
};