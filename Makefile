# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mli <mli@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/30 11:54:38 by mli               #+#    #+#              #
#    Updated: 2021/04/02 14:49:08 by mli              ###   ########.fr        #
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

NAME = webserv

CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98

LIBFT_A = libft.a
LIBFT_PATH = ./srcs/libft/

LIBS = ${addprefix ${LIBFT_PATH}, ${LIBFT_A}}

ifeq ($(f), f)
	CFLAGS += -fsanitize=address -g3
endif

SRCS_PATH = ./srcs/

ROOT_FILES = main.cpp
ROOT_HEADER = webserv.hpp

GNL_PATH = ./GNL/
GNL_FILES = get_next_line.cpp gnl_utils.cpp
GNL_HEADER = get_next_line.h

GETCONF_PATH = ./getconf/
GETCONF_FILES = getconf.cpp getstrconf.cpp utils.cpp parse_serv_value.cpp
GETCONF_HEADER = getconf.hpp

SRCS_FILES = ${ROOT_FILES} \
			 ${addprefix ${GNL_PATH}, ${GNL_FILES}} \
			 ${addprefix ${GETCONF_PATH}, ${GETCONF_FILES}}

HEADER_FILES = ${ROOT_HEADER} \
			   ${addprefix ${GNL_PATH}, ${GNL_HEADER}} \
			   ${addprefix ${GETCONF_PATH}, ${GETCONF_HEADER}}

HEADER_FULL = ${addprefix ${SRCS_PATH}, ${HEADER_FILES}}

OBJS_PATH = ./obj/
OBJS_PATHS = ${OBJS_PATH} \
			 ${OBJS_PATH}/${GNL_PATH} \
			 ${OBJS_PATH}/${GETCONF_PATH}
OBJS = ${addprefix ${OBJS_PATH}, ${SRCS_FILES:.cpp=.o}}

all: ${LIBS}
	@printf "$(BOLD)Make $(RED)$(NAME)$(EOC)"
	@echo " $(BOLD)with$(EOC) $(GREEN)$(CC)$(EOC) $(CYAN)$(CFLAGS)$(EOC): "
	@make ${NAME} -j

$(NAME): ${LIBS} ${OBJS_PATHS} ${OBJS} ${HEADER_FULL}
	@echo ""
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

test: ${LIBS} ${OBJS_PATHS} ${OBJS} ${HEADER_FULL}
	@echo ""
	@printf "$(BOLD)Make $(RED)$@$(EOC)"
	@echo " $(BOLD)with$(EOC) $(GREEN)$(CC)$(EOC) $(CYAN)$(CFLAGS)$(EOC): "
	@$(eval TMP := $(shell ls ${OBJS} | grep -v "main.o"))
	@${CC} ${CFLAGS} -o $@ ${TMP} ${LIBS}

${OBJS_PATHS}:
	@mkdir -p $@

${OBJS_PATH}%.o: ${SRCS_PATH}%.cpp ${HEADER_FULL}
	@${CC} ${CFLAGS} -c $< -o $@
	@printf "$(YELLOW)▓$(EOC)"

${LIBFT_PATH}${LIBFT_A}:
	@make -C ${LIBFT_PATH}

clean:
	@make -C ${LIBFT_PATH} fclean
	@echo "$(BOLD)$(YELLOW)Remove objs.... |$(GREEN)| done$(EOC)"
	@rm -rf ${OBJS_PATH}

fclean: clean
	@echo "$(BOLD)$(YELLOW)Remove all..... |$(GREEN)| done$(EOC)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
