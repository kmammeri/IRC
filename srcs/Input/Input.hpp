#pragma once

#include <string>
#include <vector>
#include "../Client/Client.hpp"

class Client;

using namespace std;

class Input {
	private:
 		string			_rawInput;
		vector<string>	_parsedInput;
		Client const & 	_fromClient;

	public:
		Input(string rawInput, Client const & client);

		void			parse();
		void 			printParsedInput();

		string			getRawInput() const;
		vector<string>	getParsedInput() const;
};