# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mli <mli@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/22 10:42:04 by mli               #+#    #+#              #
#    Updated: 2021/03/22 14:38:11 by mli              ###   ########.fr        #
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

NAME = mini_client

CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98

ifeq ($(f), f)
	CFLAGS += -fsanitize=address -g3
endif

GNL_PATH = ./GNL/
GNL_SRCS = get_next_line.cpp gnl_utils.cpp
GNL_FILES = ${addprefix ${GNL_PATH}, ${GNL_SRCS}}
GNL_HEADER = ${addprefix ${GNL_PATH}, get_next_line.h}

SRCS_FILES = main.cpp utils.cpp
HEADER_FILES = mini_client.hpp ${GNL_HEADER}

OBJS_PATH = ./obj/
OBJS_PATHS = ${OBJS_PATH} ${addprefix ${OBJS_PATH}, ${GNL_PATH}}
OBJS = ${addprefix ${OBJS_PATH}, ${SRCS_FILES:.cpp=.o}} \
		${addprefix ${OBJS_PATH}, ${GNL_FILES:.cpp=.o}}

all:
	@printf "$(BOLD)Make $(RED)$(NAME)$(EOC)"
	@echo " $(BOLD)with$(EOC) $(GREEN)$(CC)$(EOC) $(CYAN)$(CFLAGS)$(EOC): "
	@make ${NAME}

$(NAME): ${OBJS_PATHS} ${OBJS} ${HEADER_FILES}
	@echo ""
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS}

${OBJS_PATHS}:
	@mkdir -p $@

${OBJS_PATH}%.o: %.cpp ${HEADER_FILES}
	@${CC} ${CFLAGS} -c $< -o $@
	@printf "$(YELLOW)▓$(EOC)"

${OBJS_PATH}%.o: %.c ${HEADER_FILES}
	@${CC} ${CFLAGS} -c $< -o $@
	@printf "$(GREEN)▓$(EOC)"

clean:
	@echo "$(BOLD)$(YELLOW)Remove objs.... |$(GREEN)| done$(EOC)"
	@rm -rf ${OBJS_PATH}

fclean: clean
	@echo "$(BOLD)$(YELLOW)Remove all..... |$(GREEN)| done$(EOC)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
