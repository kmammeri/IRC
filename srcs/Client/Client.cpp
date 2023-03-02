#include "Client.hpp"

Client::Client(int fd, bool isAuth): _fd(fd), _isAuthentificated(isAuth) {}

Client::~Client() {}

int Client::getFd() const {
	return this->_fd;
}

string Client::getNickname() const {
	return this->_nickname;
}

string Client::getUsername() const {
	return this->_username;
}

bool Client::isAuthentificated() const {
	return this->_isAuthentificated;
}