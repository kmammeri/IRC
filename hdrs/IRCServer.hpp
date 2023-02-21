#pragma once
# include <string>
# include <iostream>
# include <sys/socket.h>
# include <cstdlib>
# include <map>

using namespace std;


/* Internet adresse (une structure pour des raisons historique) */
struct	in_addr {
	unsigned long s_addr;
};	

struct	sockaddr_in {
        short int         	sin_family;		/* Famille d'adresse               */
        unsigned short int	sin_port;		/* Numéro de Port                  */
    	in_addr     		sin_addr;		/* Adresse Internet                */
        unsigned char     	sin_zero[8];	/* Même taille que struct sockaddr */
};

// IRCServer class
class IRCServer {
	public:
		IRCServer(int port, const char* password);
		void start();
	
	private:
		int			_port;
		string		_password;

		int 		_sockfd;
		sockaddr_in	_sockaddr;
		// sockaddr looks like:
		// struct sockaddr {
        //        sa_family_t sa_family;
        //        char        sa_data[14];
		// }
};
