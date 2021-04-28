#ifndef S_SOCKET_HPP
# define S_SOCKET_HPP

struct s_socket {
    int             entry_socket;
    s_ipport const  *ipport;
    c_server const  *server;
    int             client_fd;
    t_sockaddr      client_addr;
    bool            is_read_ready;
    bool            is_write_ready;
    bool            is_header_read;
};

std::ostream    &operator<<(std::ostream &o, s_socket const &i);

#endif
