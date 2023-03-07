#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "../Client/Client.hpp"

class Client;

using namespace std;

class Input {
	private:
 		string			_rawInput;
		vector<string>	_tokens;

		void			_tokenise();

	public:
		Input(string rawInput);
		~Input();

		void 					printTokens() const;
		bool					empty() const;
		string const &			getRawInput() const;
		vector<string> const &	getTokens() const;
};