#include "Input.hpp"

// Constructors

Input::Input(string strInput): _rawInput(strInput) {
	this->_tokenise();
}

Input::~Input() {
	this->_rawInput.clear();
	this->_tokens.clear();
}

// Setters

void Input::_tokenise() {
	size_t i1 = 0;
	while (this->_rawInput[i1] == ' ') {
		i1++;
	}
	this->_tokens.clear();
	for (size_t i2 = i1; i2 < this->_rawInput.size(); i2++) {
		if (this->_rawInput[i2] == ' ' || this->_rawInput[i2] == '\n' || this->_rawInput[i2] == '\r') {
			string tmp(this->_rawInput, i1, i2 - i1);
			if (tmp[tmp.size() - 1] == '\n')
				tmp.erase(tmp.size() - 1);
			if (tmp[tmp.size() - 1] == '\r')
				tmp.erase(tmp.size() - 1);
			if(!tmp.empty())
				this->_tokens.push_back(tmp);
			while (this->_rawInput[i2] == ' ')
				i2++;
			i1 = i2;
		}
	}
}

// Getters

void Input::printTokens() const {
	cout << "Message tokenised give: ";
	for (size_t i = 0; i < this->_tokens.size(); i++) {
		cout << this->_tokens[i];
		if (i < (this->_tokens.size() - 1)) {
			cout << " ";
		}
	}
	cout << endl;
}

bool Input::empty() const {
	return this->_tokens.empty();
}

string const & Input::getRawInput() const {
	return this->_rawInput;
}

vector<string> const & Input::getTokens() const {
	return this->_tokens;
}
