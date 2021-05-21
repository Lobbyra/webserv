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
CFLAGS = -MMD -Wall -Wextra -std=c++98 -ferror-limit=2 -O3

LIB_A	 = lib.a
LIB_PATH = ./srcs/lib/

LIBS = ${addprefix ${LIB_PATH}, ${LIB_A}}

ifeq ($(f), f)
	CFLAGS += -fsanitize=address -g3
endif

SERVER = /tmp/www
PREREQUISITE_SCRIPT = .prerequisite.sh

SRCS_PATH = ./srcs/

ROOT_FILES  = main.cpp webserv.cpp init_clients.cpp ft_select.cpp \
			  assign_server_to_clients.cpp

DATA_STRUCTURES_PATH  = data_structures/
DATA_STRUCTURES_FILES = s_request_header.cpp s_ipport.cpp s_socket.cpp

CLASSES_PATH	= classes/
CLASSES_FILES	= c_task_queue.cpp c_callback.cpp c_location.cpp c_server.cpp \
				  c_callback_head.cpp c_callback_delete.cpp					\
				  c_callback_put.cpp c_callback_utils.cpp					\
				  c_callback_error_request.cpp c_callback_options.cpp		\
				  c_callback_trace.cpp c_callback_chunk.cpp					\
				  c_callback_get.cpp c_callback_cgi.cpp c_tmpfile.cpp		\
				  c_callback_post.cpp

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

PARSE_REQUEST_HEADER_PATH  = parse_request_header/
PARSE_REQUEST_HEADER_FILES = read_request_header.cpp parse_request.cpp		  \
							 parse_request_line.cpp  parse_request_header.cpp \
							 init_maps.cpp

READ_HEADERS_PATH  = read_headers/
READ_HEADERS_FILES = cut_buffer.cpp cut_buffer_ret.cpp find_str_buffer.cpp

UTILS_PATH	 = utils/
UTILS_FILES	 = get_keys.cpp is_space.cpp get_word_it.cpp skip_it.cpp		  \
			   is_str_num.cpp ft_isin.cpp ft_error.cpp get_word.cpp			  \
			   get_status_msg.cpp get_err_page.cpp get_status_line.cpp		  \
			   strcont_to_str.cpp lststr_to_str.cpp lststr_to_strcont.cpp	  \
			   ft_freestrs.cpp print_strs.cpp lststr_to_strs.cpp			  \
			   is_fd_ready.cpp hextodec.cpp gen_listening.cpp ft_basename.cpp \
			   lststr_len.cpp ft_dirname.cpp cgitohttp.cpp

SRCS_FILES = ${ROOT_FILES}															  \
			 ${addprefix ${PARSE_CONF_PATH}, ${PARSE_CONF_FILES}}					  \
			 ${addprefix ${UTILS_PATH}, ${UTILS_FILES}}								  \
			 $(addprefix ${PARSE_REQUEST_HEADER_PATH}, ${PARSE_REQUEST_HEADER_FILES}) \
			 $(addprefix ${CLASSES_PATH}, ${CLASSES_FILES})							  \
			 $(addprefix ${DATA_STRUCTURES_PATH}, ${DATA_STRUCTURES_FILES})			  \
			 $(addprefix ${READ_HEADERS_PATH}, ${READ_HEADERS_FILES})

OBJS_PATH	= ./.objs/
OBJS_PATHS	= ${OBJS_PATH} \
			 ${OBJS_PATH}/${UTILS_PATH}							\
			 ${OBJS_PATH}/${CLASSES_PATH}						\
			 ${OBJS_PATH}/${PARSE_CONF_PATH}					\
			 ${OBJS_PATH}/${PARSE_REQUEST_HEADER_PATH}			\
			 ${OBJS_PATH}/${PARSE_CONF_PATH}/${PARSE_FUNS_PATH} \
			 ${OBJS_PATH}/${DATA_STRUCTURES_PATH}				\
			 ${OBJS_PATH}/${READ_HEADERS_PATH}
OBJS		= ${addprefix ${OBJS_PATH}, ${SRCS_FILES:.cpp=.o}}
MMD_FILES	= ${OBJS:.o=.d}

INCL_PATHS = ${SRCS_PATH}/. \
			 ${LIB_PATH}										\
			 ${SRCS_PATH}/${PARSE_CONF_PATH}					\
			 ${SRCS_PATH}/${PARSE_CONF_PATH}/${PARSE_FUNS_PATH} \
			 ${SRCS_PATH}/${UTILS_PATH}							\
			 ${SRCS_PATH}/${PARSE_REQUEST_HEADER_PATH}			\
			 ${SRCS_PATH}/${CLASSES_PATH}						\
			 ${SRCS_PATH}/${DATA_STRUCTURES_PATH}				\
			 ${SRCS_PATH}/${READ_HEADERS_PATH}

INCL_FLAGS = ${addprefix -I, ${INCL_PATHS}}

all:
	@./${PREREQUISITE_SCRIPT}
	@echo "👷 : If you want sanitize add f=f !"
	@make f="$f" -C ${LIB_PATH}
	@printf "$(BOLD)Make $(RED)$(NAME)$(EOC)"
	@echo " $(BOLD)with$(EOC) $(GREEN)$(CC)$(EOC) $(CYAN)$(CFLAGS)$(EOC): "
	@make ${NAME} -j

-include ${MMD_FILES}

$(NAME): ${LIBS} ${OBJS} ${SERVER} | ${OBJS_PATHS}
	@echo ""
	@${CC} ${CFLAGS} ${INCL_FLAGS} -o ${NAME} ${OBJS} ${LIBS}

test: ${LIBS} ${OBJS} | ${OBJS_PATHS}
	@echo ""
	@echo "👷 : If you want sanitize add f=f !"
	@printf "$(BOLD)Make $(RED)$@$(EOC)"
	@echo " $(BOLD)with$(EOC) $(GREEN)$(CC)$(EOC) $(CYAN)$(CFLAGS)$(EOC): "
	@$(eval TMP := $(shell ls ${OBJS} | grep -v "main.o"))
	@${CC} ${CFLAGS} ${INCL_FLAGS} -o $@ ${TMP} ${LIBS}

${OBJS_PATHS}:
	@mkdir -p $@

${OBJS_PATH}%.o: ${SRCS_PATH}%.cpp | ${OBJS_PATHS}
	@${CC} ${CFLAGS} ${INCL_FLAGS} -c $< -o $@
	@printf "$(YELLOW)▓$(EOC)"

${LIB_PATH}${LIB_A}:
	@make f="$f" -C ${LIB_PATH}

${SERVER}:
	@cp -rf ./tools/docker_nginx/www $@
	@$@/run.sh $@

clean:
	@make -C ${LIB_PATH} fclean
	@echo "$(BOLD)$(YELLOW)Remove objs.... |$(GREEN)| done$(EOC)"
	@rm -rf ${OBJS_PATH}

fclean: clean
	@echo "$(BOLD)$(YELLOW)Remove all..... |$(GREEN)| done$(EOC)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
