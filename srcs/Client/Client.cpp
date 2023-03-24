#include "Client.hpp"

Client::Client(int fd, string const & hostname):
	_fd(fd), 
	_hostname(hostname),
	_isAuthentificated(false),
	_isRegistered(false) {}

Client::~Client() {}

void Client::sendReply(string reply) const {
	reply + "\r\n";
	int n = send(this->_fd, reply.c_str(), reply.length(), 0);
	if (n < 0) {
		throw runtime_error("Error: send() failed");
	}
	cout << "Sent message to client " << this->_fd << ": " << reply << endl;

}


// Setters

void Client::setUsername(string const & username) {
	this->_username = username;
}

void Client::setChatwith(string const & chatwith) {
	this->_chatwith = chatwith;
}

void Client::setNickname(string const & nickname) {
	this->_nickname = nickname;
}

void Client::setRealname(string const & realname) {
	this->_realname = realname;
}

void Client::setServername(string const & servername) {
	this->_servername = servername;
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

string const & Client::getChatwith() const {
	return this->_chatwith;
}

string const & Client::getNickname() const {
	return this->_nickname;
}

string const & Client::getUsername() const {
	return this->_username;
}

string const & Client::getServername() const {
	return this->_servername;
}

bool Client::isAuthentificated() const {
	return this->_isAuthentificated;
}

bool Client::isRegistered() const {
	return this->_isRegistered;
}

string const & Client::getRealname() const {
	return this->_realname;
}

string const & Client::getHostname() const {
	return this->_hostname;
}