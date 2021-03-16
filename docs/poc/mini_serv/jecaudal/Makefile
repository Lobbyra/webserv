NAME		=	mini_server

SRCS		=	lib.cpp					\
				main.cpp				\
				mini_serv.cpp			\
				get_next_line.cpp		\
				get_next_line_utils.cpp

CPP			=	clang++

%.o: %.cpp
				$(CPP) $(CPPFLAGS) -c $<

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS		+=	-Wall -Werror -Wextra

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(CPP) -o $(NAME) $(CPPFLAGS) $(OBJS)

san			:	$(OBJS)
				$(CPP) -o $(NAME) -fsanitize=address $(CPPFLAGS) $(OBJS)

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -f $(NAME)

re			:	fclean all
