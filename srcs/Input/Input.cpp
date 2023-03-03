#include "Input.hpp"
#include <iostream>

Input::Input(string strInput, Client const & client):
 	_rawInput(strInput),
	_fromClient(client)
	{}


void Input::printParsedInput() {
		cout << "Message receive form: " << this->_fromClient.getFd() << " => ";
		for (size_t i = 0; i < this->_parsedInput.size(); i++) {
			cout << this->_parsedInput[i];
			if (i < (this->_parsedInput.size() - 1)) {
				cout << " ";
			}
		}
		cout << endl;
}

void Input::parse() {

	size_t i1 = 0;
	while (this->_rawInput[i1] == ' ') {
		i1++;
	}
	this->_parsedInput.clear();
	for (size_t i2 = i1; i2 < this->_rawInput.size(); i2++) {
		if (this->_rawInput[i2] == ' ' || this->_rawInput[i2] == '\n' || this->_rawInput[i2] == '\r') {
			string tmp(this->_rawInput, i1, i2 - i1);
			if (tmp[tmp.size() - 1] == '\n')
				tmp.erase(tmp.size() - 1);
			if (tmp[tmp.size() - 1] == '\r')
				tmp.erase(tmp.size() - 1);
			if(!tmp.empty())
				this->_parsedInput.push_back(tmp);
			while (this->_rawInput[i2] == ' ')
				i2++;
			i1 = i2;
		}
	}
}