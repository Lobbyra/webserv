#ifndef WEBSERV_HPP
# define WEBSERV_HPP

// C++ HEADERS
# include <queue>
# include <string>
# include <iostream>
# include <exception>
# include <algorithm>

// C HEADERS
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <netinet/in.h> // struct sockaddr_in

# define SERVER_NAME "drunkserv 0.1"

extern int indent_lvl;

# include "lib/lib.hpp"
# include "utils/utils.hpp"

#include "s_ipport.hpp"

#include "colors.hpp"

bool    operator==(s_ipport const &a, s_ipport const &b);
bool    operator!=(s_ipport const &a, s_ipport const &b);

# include "std_typedefs.hpp"

# include "c_location.hpp"
# include "c_server.hpp"
# include "parse_conf.hpp"

# include "s_request_header.hpp"

#include "s_socket.hpp"

#include "our_typedefs.hpp"

std::list<c_server>     parse_conf(std::string path);
void                    webserv(std::list<c_server> const &conf);
t_socketlst             init_clients(std::list<c_server> const &conf);
void                    ft_select(t_socketlst *const clients);

void    assign_server_to_clients(std::list<c_server> const &conf, \
    t_socketlst *const clients, std::list<s_request_header> const &reqs);

# include "parse_request.hpp"

void            init_callback(t_socketlst clients,
                              std::list<s_request_header> requests);

# include "c_callback.hpp"
# include "c_task_queue.hpp"

#endif // *************************************************** WEBSERV_HPP end //
