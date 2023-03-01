#pragma once

#include <iostream>
#include <string>

using namespace std;

class ACommand {
	public:
		virtual void execute(int clientfd, string msg) = 0;
};