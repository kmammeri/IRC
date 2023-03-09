#include "Client.hpp"

Client::Client(int fd):
	_fd(fd), 
	_isAuthentificated(false),
	_isRegistered(false) {}

Client::~Client() {}

void Client::sendReply(string const & code, string const & reply) const {
	string msg = ":" + string(SERVER_NAME) + " " + code + " :" + this->_nickname + " " + reply + "\r";
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

void Client::setAuthentification(bool auth) {
	this->_isAuthentificated = auth;
}

void Client::setRegistration(bool reg) {
	this->_isRegistered = reg;
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

bool Client::isRegistered() const {
	return this->_isRegistered;
}