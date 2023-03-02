#pragma once

#include <string>
#include <vector>

using namespace std;

class Input {
	private:
		string			_rawInput;
		vector<string>	_parsedInput;

	public:
		Input(string rawInput);

		void			parse();
		string			getRawInput() const;
		vector<string>	getParsedInput() const;
};