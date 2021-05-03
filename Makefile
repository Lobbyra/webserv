EOC  = \033[0m
BOLD = \033[1m
RED    = \033[91m
CYAN   = \033[96m
GREEN  = \033[92m
DBLUE  = \033[94m
PURPLE = \033[95m
YELLOW = \033[93m

# ############################################################################ #

NAME = webserv

CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -ferror-limit=2

LIB_A	 = lib.a
LIB_PATH = ./srcs/lib/

LIBS = ${addprefix ${LIB_PATH}, ${LIB_A}}

f=f
ifeq ($(f), f)
	CFLAGS += -fsanitize=address -g3
endif

SRCS_PATH = ./srcs/

ROOT_FILES  = main.cpp webserv.cpp init_clients.cpp ft_select.cpp \
			  assign_server_to_clients.cpp
ROOT_HEADER = webserv.hpp

DATA_STRUCTURES_PATH  = data_structures/
DATA_STRUCTURES_FILES = s_request_header.cpp s_ipport.cpp s_socket.cpp

CLASSES_PATH	= classes/
CLASSES_FILES	= c_task_queue.cpp c_callback.cpp c_location.cpp c_server.cpp \
				  c_callback_head.cpp c_callback_delete.cpp					\
				  c_callback_put.cpp c_callback_utils.cpp					\
				  c_callback_error_request.cpp c_callback_options.cpp		\
				  c_callback_get.cpp c_callback_cgi.cpp
CLASSES_HEADERS	= c_task_queue.hpp c_callback.hpp c_location.hpp c_server.hpp

PARSE_FUNS_PATH	 = parse_funs/
PARSE_FUNS_FILES = parse_autoindex.cpp parse_listen.cpp						  \
				   parse_client_max_body_size.cpp parse_root.cpp			  \
				   parse_fastcgi_param.cpp skip_k_get_value.cpp				  \
				   parse_server_name.cpp parse_index.cpp parse_error_page.cpp \
				   parse_location.cpp parse_fastcgi_pass.cpp parse_methods.cpp

PARSE_CONF_PATH 	= parse_conf/
PARSE_CONF_FILES	= ${addprefix ${PARSE_FUNS_PATH}, ${PARSE_FUNS_FILES}} \
					  get_conf.cpp skip_param.cpp init_maps.cpp			   \
				   	  check_key.cpp get_serv.cpp parse_conf.cpp
PARSE_CONF_HEADER	= parse_conf.hpp

PARSE_REQUEST_HEADER_PATH  = parse_request_header/
PARSE_REQUEST_HEADER_FILES = read_request_header.cpp parse_request.cpp		  \
							 parse_request_line.cpp  parse_request_header.cpp \
							 init_maps.cpp

UTILS_PATH	 = utils/
UTILS_FILES	 = get_keys.cpp is_space.cpp get_word_it.cpp skip_it.cpp	  \
			   is_str_num.cpp ft_isin.cpp ft_error.cpp get_word.cpp		  \
			   get_status_msg.cpp get_err_page.cpp get_status_line.cpp	  \
			   strcont_to_str.cpp lststr_to_str.cpp lststr_to_strcont.cpp

UTILS_HEADER = utils.hpp insert_stream_cont.hpp

SRCS_FILES = ${ROOT_FILES} \
			 ${addprefix ${PARSE_CONF_PATH}, ${PARSE_CONF_FILES}} \
			 ${addprefix ${UTILS_PATH}, ${UTILS_FILES}}	\
			 $(addprefix ${PARSE_REQUEST_HEADER_PATH}, ${PARSE_REQUEST_HEADER_FILES}) \
			 $(addprefix ${CLASSES_PATH}, ${CLASSES_FILES}) \
			 $(addprefix ${DATA_STRUCTURES_PATH}, ${DATA_STRUCTURES_FILES})

HEADER_FILES = ${ROOT_HEADER} \
			   ${addprefix ${PARSE_CONF_PATH}, ${PARSE_CONF_HEADER}} \
			   ${addprefix ${UTILS_PATH}, ${UTILS_HEADER}}	\
			   ${addprefix ${PARSE_REQUEST_HEADER_PATH}, ${PARSE_REQUEST_HEADER_HEADER}} \
			   ${addprefix ${CLASSES_PATH}, ${CLASSES_HEADERS}}

HEADER_FULL = ${addprefix ${SRCS_PATH}, ${HEADER_FILES}}

OBJS_PATH  = ./obj/
OBJS_PATHS = ${OBJS_PATH} \
			 ${OBJS_PATH}/${UTILS_PATH}							\
			 ${OBJS_PATH}/${CLASSES_PATH}						\
			 ${OBJS_PATH}/${PARSE_CONF_PATH}					\
			 ${OBJS_PATH}/${PARSE_REQUEST_HEADER_PATH}			\
			 ${OBJS_PATH}/${PARSE_CONF_PATH}/${PARSE_FUNS_PATH} \
			 ${OBJS_PATH}/${DATA_STRUCTURES_PATH}
OBJS	   = ${addprefix ${OBJS_PATH}, ${SRCS_FILES:.cpp=.o}}

INCL_PATHS = ${SRCS_PATH}/. \
			 ${SRCS_PATH}/${PARSE_CONF_PATH}					\
			 ${SRCS_PATH}/${PARSE_CONF_PATH}/${PARSE_FUNS_PATH} \
			 ${SRCS_PATH}/${UTILS_PATH}							\
			 ${SRCS_PATH}/${PARSE_REQUEST_HEADER_PATH}			\
			 ${SRCS_PATH}/${CLASSES_PATH}						\
			 ${LIB_PATH}										\
			 ${SRCS_PATH}/${DATA_STRUCTURES_PATH}


INCL_FLAGS = ${addprefix -I, ${INCL_PATHS}}

all: ${LIBS}
	@printf "$(BOLD)Make $(RED)$(NAME)$(EOC)"
	@echo " $(BOLD)with$(EOC) $(GREEN)$(CC)$(EOC) $(CYAN)$(CFLAGS)$(EOC): "
	@make ${NAME} -j

$(NAME): ${LIBS} ${OBJS_PATHS} ${OBJS} ${HEADER_FULL}
	@echo ""
	@${CC} ${CFLAGS} ${INCL_FLAGS} -o ${NAME} ${OBJS} ${LIBS}

test: ${LIBS} ${OBJS_PATHS} ${OBJS} ${HEADER_FULL}
	@echo ""
	@printf "$(BOLD)Make $(RED)$@$(EOC)"
	@echo " $(BOLD)with$(EOC) $(GREEN)$(CC)$(EOC) $(CYAN)$(CFLAGS)$(EOC): "
	@$(eval TMP := $(shell ls ${OBJS} | grep -v "main.o"))
	@${CC} ${CFLAGS} ${INCL_FLAGS} -o $@ ${TMP} ${LIBS}

${OBJS_PATHS}:
	@mkdir -p $@

${OBJS_PATH}%.o: ${SRCS_PATH}%.cpp ${HEADER_FULL}
	@${CC} ${CFLAGS} ${INCL_FLAGS} -c $< -o $@
	@printf "$(YELLOW)▓$(EOC)"

${LIB_PATH}${LIB_A}:
	@make f="$f" -C ${LIB_PATH}

clean:
	@make -C ${LIB_PATH} fclean
	@echo "$(BOLD)$(YELLOW)Remove objs.... |$(GREEN)| done$(EOC)"
	@rm -rf ${OBJS_PATH}

fclean: clean
	@echo "$(BOLD)$(YELLOW)Remove all..... |$(GREEN)| done$(EOC)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
