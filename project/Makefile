NAME 			= ircserv
CC 				= c++
FLAGS			= -Wall -Wextra -Werror -std=c++98
RM 				= rm -rf

SRC_PATH 		= srcs/
SRCS 			=				\
	main.cpp					\
	server/Server.cpp			\
	server/onChannelEvent.cpp	\
	server/onUserEvent.cpp		\
	server/User.cpp				\
	commands/Command.cpp		\
	commands/cap.cpp			\
	commands/pass.cpp			\
	commands/join.cpp			\
	commands/kick.cpp			\
	commands/part.cpp			\
	commands/quit.cpp			\
	commands/mode.cpp			\
	commands/who.cpp			\
	commands/user.cpp			\
	commands/nick.cpp			\
	commands/invite.cpp			\
	commands/topic.cpp			\
	commands/privmsg.cpp		\
	channel/Channel.cpp			\
	channel/onModeEvent.cpp		\

HEADER_PATH 	= includes/
HEADERS			=				\
	Server.hpp					\
	Command.hpp					\
	User.hpp					\
	Channel.hpp					\
	utils/Numerics.hpp			\

DEPENDENCIES	= $(patsubst %.hpp, $(HEADER_PATH)%.hpp, $(HEADERS))

OBJS_DIR		= .objects/
OBJS			=	$(patsubst %.cpp, $(OBJS_DIR)%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS) Makefile
	$(CC) $(FLAGS) -I$(HEADER_PATH) $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o : $(SRC_PATH)%.cpp $(DEPENDENCIES)
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -I$(HEADER_PATH) -c $< -o $@

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
