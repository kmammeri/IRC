liens utils pour la mise en place du serveur:
- http://vidalc.chez.com/lf/socket.html

TODO list:
	- s'authentifier avec le mot de pass
	- recevoir et parser les messages
	- gerer les commades partiels
	- concatener si besoin les messages :: overflow et ^D
	- bien repondre en fonction de ce qu'on recoit
	- faire les commandes
	- Attention les commandes empty avec nc abort avec fsanityze
			::JOIN
			::PART
			::TOPIC -> Operator
			::NAMES
			::LIST
			::INVITE -> Operator
			::KICK -> Operator
			::PRIVMSG
			::MODE -> Opertaor
			::NOTICE -> (Operator ?) -> Fait pariel que PRIVMSG	
			::PASS
			::QUIT ???