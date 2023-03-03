#pragma once

#include <string>
#include <vector>
#include "../Client/Client.hpp"

class Client;

using namespace std;

class Input {
	private:
 		string			_rawInput;
		vector<string>	_command;

	public:
		Input(string rawInput);

		void			cut();
		void 			printCommand() const;
		bool			empty() const;
		void 			clear();

		string const &			getRawInput() const;
		vector<string> const &	getCommand() const;
};