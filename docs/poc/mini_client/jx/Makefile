# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jereligi <jereligi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/07 15:03:53 by jereligi          #+#    #+#              #
#    Updated: 2021/04/07 17:25:16 by jereligi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mini_client

SRC = 	mini_client.cpp	

OBJ = $(SRC:.cpp=.o)

CC = clang++

CPPFLAGS = -Wall -Wextra -Werror -std=c++98

all : $(NAME)

$(NAME) :	$(OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
			
clean :
			rm -rf $(OBJ)

fclean : clean
			rm -rf $(NAME)

re : fclean all
