#ifndef S_SOCKET_HPP
# define S_SOCKET_HPP

#include <iostream> // operator<<

#include <sys/types.h> // sockaddr
#include <sys/socket.h>

#include "s_ipport.hpp"
#include "c_server.hpp"
#include "s_request_header.hpp"

struct s_socket {
    int              client_fd;
    int              entry_socket;
    bool             is_read_ready;
    bool             is_write_ready;
    bool             is_header_read;
    bool             is_status_line_read;
    bool             is_callback_created;
    sockaddr         client_addr;
    s_ipport const   *ipport;
    c_server const   *server;
    s_request_header headers;
    std::list<char*> buf_header;
};

void    reset_socket(s_socket *s);

std::ostream    &operator<<(std::ostream &o, s_socket const &i);
std::ostream    &operator<<(std::ostream& os, const std::list<s_socket>& v);

#endif
