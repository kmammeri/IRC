NAME		=	ircserv	

INC			=	srcs/ircserv.hpp \
				srcs//Server/IRCServer.hpp \
				srcs//Client/Client.hpp \
				srcs/Channel/Channel.hpp \
				srcs/Commands/Commands.hpp \
				srcs/utils/utils.hpp

SRCS 		=	srcs/ircserv.cpp \
				srcs/Server/IRCServer.cpp \
				srcs/Client/Client.cpp \
				srcs/Channel/Channel.cpp \
				srcs/Commands/PASS.cpp \
				srcs/Commands/USER.cpp \
				srcs/Commands/NICK.cpp \
				srcs/Commands/JOIN.cpp \
				srcs/utils/utils.cpp


OBJS 		=	${addprefix objs/, ${SRCS:.cpp=.o}}

CC 			=	c++
CFLAGS		=	-Wall -Werror -Wextra -std=c++98 #-pedantic -O3
RM 			=	rm -rf

objs/%.o: 	%.cpp ${INC} Makefile
			@mkdir -p $(dir $@)
			$(CC) ${CFLAGS} -I ./objs -c $< -o $@

all:		 ${NAME}

${NAME}: 	${OBJS} ${INC}
			$(CC) ${CFLAGS} -o $(NAME) ${OBJS}

clean:
			${RM} objs/

fclean: 	clean
			${RM} ${NAME}

re: 		fclean all

.PHONY: 	all clean fclean re