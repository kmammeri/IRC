#pragma once

#include "ACommand.hpp"
#include <string>

class JoinCmd: public ACommand {
	public:
		virtual void execute(int clientfd, string msg);
};