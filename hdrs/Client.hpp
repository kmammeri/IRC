class Client {
	private:
		int		_sockfd;
		string	_nickname;
		string	_username;
		int		_isOperator;
	
	public:
		Client(int sockfd);
		~Client();
};
