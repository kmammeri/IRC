#include "Client.hpp"

Client::Client(int fd, bool isAuth): _fd(fd), _isAuthentificated(isAuth) {}

Client::~Client() {}

void Client::sendReply(string const & code, string const & reply) const {
	string msg = ":" + this->_nickname + " " + code + " " + reply + "\r";
	int n = send(this->_fd, msg.c_str(), msg.length(), 0);
	if (n < 0) {
		throw runtime_error("Error: send() failed");
	}
	cout << "Sent message to client " << this->_fd << ": " << msg << endl;

}


// Setters

void Client::setUsername(string const & username) {
	this->_username = username;
}

void Client::setNickname(string const & nickname) {
	this->_nickname = nickname;
}

void Client::setAuthentification(bool Auth) {
	this->_isAuthentificated = Auth;
}

// Getters

int Client::getFd() const {
	return this->_fd;
}

string const & Client::getNickname() const {
	return this->_nickname;
}

string const & Client::getUsername() const {
	return this->_username;
}

bool Client::isAuthentificated() const {
	return this->_isAuthentificated;
}