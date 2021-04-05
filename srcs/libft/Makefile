# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mli <mli@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/01 14:41:08 by mli               #+#    #+#              #
#    Updated: 2021/04/01 16:26:42 by mli              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EOC = \033[0m
BOLD = \033[1m
RED = \033[91m
GREEN = \033[92m
YELLOW = \033[93m
DBLUE = \033[94m
PURPLE = \033[95m
CYAN = \033[96m

# ############################################################################ #

NAME = libft.a

CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98

ifeq ($(f), f)
	CFLAGS += -fsanitize=address -g3
endif

LIBFT_SRCS = ft_memset.cpp ft_bzero.cpp ft_strlen.cpp ft_toupper.cpp ft_tolower.cpp \
			 ft_strchr.cpp ft_strrchr.cpp ft_strncmp.cpp ft_strlcpy.cpp ft_strlcat.cpp \
			 ft_strnstr.cpp ft_atoi.cpp ft_isalpha.cpp ft_isdigit.cpp ft_isalnum.cpp \
			 ft_isascii.cpp ft_isprint.cpp ft_memcpy.cpp ft_memccpy.cpp ft_memmove.cpp \
			 ft_memchr.cpp ft_memcmp.cpp ft_calloc.cpp ft_substr.cpp \
			 ft_strtrim.cpp ft_strjoin.cpp ft_split.cpp ft_itoa.cpp ft_strmapi.cpp \
			 ft_strcmp.cpp ft_memalloc.cpp ft_free.cpp ft_atoi_ptr.cpp ft_nbrlen.cpp \
			 ft_abs.cpp ft_itoa_lbase.cpp

SRCS_FILES = ${LIBFT_SRCS}
HEADER_FILES = libft.h

OBJS_PATH = ./obj/
OBJS = ${addprefix ${OBJS_PATH}, ${SRCS_FILES:.cpp=.o}}

all:
	@echo "$(BOLD)Make $(RED)$(NAME)$(EOC):"
	@make ${NAME} -j

$(NAME): ${OBJS_PATH} ${OBJS} ${HEADER_FILES}
	@echo ""
	@ar rcs ${NAME} ${OBJS}

${OBJS_PATH}:
	@mkdir -p $@

${OBJS_PATH}%.o: %.cpp ${HEADER_FILES}
	@${CC} ${CFLAGS} -c $< -o $@
	@printf "$(YELLOW)▓$(EOC)"

clean:
	@echo "$(BOLD)$(YELLOW)Remove objs libft|$(GREEN)| done$(EOC)"
	@rm -rf ${OBJS_PATH}

fclean: clean
	@echo "$(BOLD)$(YELLOW)Remove all libft |$(GREEN)| done$(EOC)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
