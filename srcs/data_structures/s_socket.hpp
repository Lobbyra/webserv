#ifndef S_SOCKET_HPP
# define S_SOCKET_HPP

#include <iostream> // operator<<

#include <sys/types.h> // sockaddr
#include <sys/socket.h>

#include "s_ipport.hpp"
#include "c_server.hpp"
#include "s_request_header.hpp"

struct s_similar_get_req {
    std::string     host;
    std::string     respons;
    std::string     path_respons;
    s_ipport const  *ipport;
    time_t          last_access;
};

struct s_socket {
    int                 client_fd;
    int                 entry_socket;
    bool                is_read_ready;
    bool                is_write_ready;
    bool                is_header_read;
    bool                is_status_line_read;
    bool                is_callback_created;
    sockaddr            client_addr;
    s_ipport const      *ipport;
    c_server const      *server;
    s_request_header    headers;
    std::list<char*>    buffer;
    s_similar_get_req   *similar_req;
};

void    reset_socket(s_socket *s);

std::ostream    &operator<<(std::ostream &o, s_socket const &i);
std::ostream    &operator<<(std::ostream& os, const std::list<s_socket>& v);

#endif
