# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mli <mli@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/30 11:54:38 by mli               #+#    #+#              #
#    Updated: 2021/04/05 16:57:17 by mli              ###   ########.fr        #
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

LIB_A = lib.a
LIB_PATH = ./srcs/lib/
LIB_HEADER = lib.hpp

LIBS = ${addprefix ${LIB_PATH}, ${LIB_A}}

ifeq ($(f), f)
	CFLAGS += -fsanitize=address -g3
endif

SRCS_PATH = ./srcs/

ROOT_FILES = main.cpp
ROOT_HEADER = webserv.hpp data_structures.hpp

GETCONF_PATH = ./getconf/
GETCONF_FILES = getconf.cpp getstrconf.cpp utils.cpp parse_serv_value.cpp
GETCONF_HEADER = getconf.hpp

SRCS_FILES = ${ROOT_FILES} \
			 ${addprefix ${GETCONF_PATH}, ${GETCONF_FILES}}

HEADER_FILES = ${ROOT_HEADER} \
			   ${addprefix ${GETCONF_PATH}, ${GETCONF_HEADER}}

HEADER_FULL = ${addprefix ${SRCS_PATH}, ${HEADER_FILES}} \
			  ${addprefix ${LIB_PATH}, ${LIB_HEADER}}

OBJS_PATH = ./obj/
OBJS_PATHS = ${OBJS_PATH} \
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

${LIB_PATH}${LIB_A}:
	@make -C ${LIB_PATH}

clean:
	@make -C ${LIB_PATH} fclean
	@echo "$(BOLD)$(YELLOW)Remove objs.... |$(GREEN)| done$(EOC)"
	@rm -rf ${OBJS_PATH}

fclean: clean
	@echo "$(BOLD)$(YELLOW)Remove all..... |$(GREEN)| done$(EOC)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
