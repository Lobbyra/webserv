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

LIBS = ${addprefix ${LIB_PATH}, ${LIB_A}}

ifeq ($(f), f)
	CFLAGS += -fsanitize=address -g3
endif

SRCS_PATH = ./srcs/

ROOT_FILES = main.cpp c_server.cpp c_location.cpp
ROOT_HEADER = webserv.hpp

PARSE_CONF_PATH = ./parse_conf/
PARSE_FUNS_PATH = ./parse_funs/
PARSE_FUNS_FILES = parse_autoindex.cpp            parse_listen.cpp			\
				   parse_client_max_body_size.cpp parse_root.cpp			\
				   parse_fastcgi_param.cpp        skip_k_get_value.cpp		\
				   parse_server_name.cpp parse_index.cpp parse_error_page.cpp

PARSE_CONF_FILES = ${addprefix ${PARSE_FUNS_PATH}, ${PARSE_FUNS_FILES}}		 \
				   getconf.cpp get_location.cpp skip_param.cpp init_maps.cpp \
				   check_key.cpp
PARSE_CONF_HEADER = parse_conf.hpp

UTILS_PATH = ./utils/
UTILS_FILES = get_keys.cpp is_space.cpp get_word_it.cpp skip_it.cpp			\
			  is_str_num.cpp ft_isin.cpp
UTILS_HEADER = utils.hpp insert_stream_cont.hpp

SRCS_FILES = ${ROOT_FILES} \
			 ${addprefix ${PARSE_CONF_PATH}, ${PARSE_CONF_FILES}} \
			 ${addprefix ${UTILS_PATH}, ${UTILS_FILES}}

HEADER_FILES = ${ROOT_HEADER} \
			   ${addprefix ${PARSE_CONF_PATH}, ${PARSE_CONF_HEADER}} \
			   ${addprefix ${UTILS_PATH}, ${UTILS_HEADER}}

HEADER_FULL = ${addprefix ${SRCS_PATH}, ${HEADER_FILES}}

OBJS_PATH = ./obj/
OBJS_PATHS = ${OBJS_PATH} \
			 ${OBJS_PATH}/${PARSE_CONF_PATH} \
			 ${OBJS_PATH}/${PARSE_CONF_PATH}/${PARSE_FUNS_PATH} \
			 ${OBJS_PATH}/${UTILS_PATH}
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
