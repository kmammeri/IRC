#include <cstring>


class Channel {
	private:
		set<Client>		_usersInChannel;
	public:
		Channel(/* args */);
		~Channel();
};