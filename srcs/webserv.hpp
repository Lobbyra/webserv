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

bool    ft_select(std::list<s_socket> *const clients,
                  s_similar_get_req *similar_req);

void    similar_get_req_sender(std::list<s_socket> *clients,
                                s_similar_get_req *similar_req);
void    similar_get_req_checker(std::list<s_socket> *clients,
                                s_similar_get_req *similar_req);

void    init_clients(std::list<c_server> const &conf,
                     std::list<s_socket> *clients);

std::list<s_request_header> parse_request(std::list<s_socket> *const clients);

void    assign_server_to_clients(std::list<c_server> const &conf,
                                 std::list<s_socket> *const clients);

#endif
