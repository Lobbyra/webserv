#ifndef S_SOCKET_HPP
# define S_SOCKET_HPP

#include "s_ipport.hpp"
#include "c_server.hpp"

#include <iostream> // operator<<

#include <sys/types.h> // sockaddr
#include <sys/socket.h>

struct s_socket {
    int             entry_socket;
    s_ipport const  *ipport;
    c_server const  *server;
    int             client_fd;
    sockaddr      client_addr;
    bool            is_read_ready;
    bool            is_write_ready;
    bool            is_header_read;
};

std::ostream    &operator<<(std::ostream &o, s_socket const &i);
std::ostream    &operator<<(std::ostream& os, const std::list<s_socket>& v);

#endif
