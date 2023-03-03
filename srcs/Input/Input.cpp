#include "Input.hpp"
#include <iostream>

Input::Input(string strInput):
 	_rawInput(strInput) {}

void Input::cut() {
	size_t i1 = 0;
	while (this->_rawInput[i1] == ' ') {
		i1++;
	}
	this->_command.clear();
	for (size_t i2 = i1; i2 < this->_rawInput.size(); i2++) {
		if (this->_rawInput[i2] == ' ' || this->_rawInput[i2] == '\n' || this->_rawInput[i2] == '\r') {
			string tmp(this->_rawInput, i1, i2 - i1);
			if (tmp[tmp.size() - 1] == '\n')
				tmp.erase(tmp.size() - 1);
			if (tmp[tmp.size() - 1] == '\r')
				tmp.erase(tmp.size() - 1);
			if(!tmp.empty())
				this->_command.push_back(tmp);
			while (this->_rawInput[i2] == ' ')
				i2++;
			i1 = i2;
		}
	}
}

void Input::printCommand() const {
	cout << "Message tokenised give: ";
	for (size_t i = 0; i < this->_command.size(); i++) {
		cout << this->_command[i];
		if (i < (this->_command.size() - 1)) {
			cout << " ";
		}
	}
	cout << endl;
}

bool Input::empty() const {
	return this->_command.empty();
}

string const & Input::getRawInput() const {
	return this->_rawInput;
}

vector<string> const & Input::getCommand() const {
	return this->_command;
}

void Input::clear() {
	this->_rawInput.clear();
	this->_command.clear();
}