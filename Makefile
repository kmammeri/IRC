NAME		=	ircserv	

INC			=	hdrs/ircserv.hpp \
				hdrs/IRCServer.hpp \
				hdrs/Client.hpp \
				hdrs/Channel.hpp \
				hdrs/Commands/JoinCmd.hpp \
				hdrs/utils.hpp

SRCS 		=	srcs/ircserv.cpp \
				srcs/IRCServer.cpp \
				srcs/Client.cpp \
				srcs/Channel.cpp \
				srcs/Commands/JoinCmd.cpp \
				utils/utils.cpp


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