#include "Input.hpp"
#include <iostream>

Input::Input(string strInput):
 	_rawInput(strInput) {}

void Input::parse() {

	size_t i1 = 0;

	this->_parsedInput.clear();
	for (size_t i2 = 0; i2 < this->_rawInput.size(); i2++) {
		if (this->_rawInput[i2] == ' ' || (this->_rawInput[i2] == '\n' && this->_rawInput[i2 - 1] == '\r')) {
			string tmp(this->_rawInput, i1, i2 - i1);
			if (tmp[tmp.size() - 1] == '\n')
				tmp.erase(tmp.size() - 1);
			if (tmp[tmp.size() - 1] == '\r')
				tmp.erase(tmp.size() - 1);
			this->_parsedInput.push_back(tmp);
			i1 = i2 + 1;
		}
	}
	for (size_t i = 0; i < this->_parsedInput.size(); i++) {
		cout << "this->_parsedInput[" << i << "] = " << this->_parsedInput[i] << endl;
	}
}