#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <list>
# include <iostream>

# include <signal.h>
# include <sys/socket.h>

# include "s_socket.hpp"
# include "c_server.hpp"
# include "parse_conf.hpp"
# include "c_task_queue.hpp"
# include "our_typedefs.hpp"
# include "s_request_header.hpp"

bool    read_headers(std::list<s_socket> *clients);

void    webserv(std::list<c_server> const &conf);

bool    ft_select(t_socketlst *const clients, struct s_similar_get_req *similar_req);

void    similar_get_req_manager(t_socketlst *clients, struct s_similar_get_req *similar_req);

void    init_clients(std::list<c_server> const &conf, t_socketlst *clients);

std::list<s_request_header>     parse_request(t_socketlst *const clients);

void    assign_server_to_clients(std::list<c_server> const &conf, \
                                 t_socketlst *const clients);

#endif
