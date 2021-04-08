#ifndef C_SERVER_HPP
# define C_SERVER_HPP

# include "webserv.hpp"

class   c_location;

class   c_server {
public:

    c_server(void);
    c_server(c_server const &src);
    c_server &operator=(c_server const &src);
    virtual ~c_server();

    int                     client_max_body_size;
    t_strlst                index;
    s_ipport                listen;
    t_strlst                server_name;
    std::string             root;
    std::string             autoindex;
    t_cgi_param             fastcgi_param;
    t_error_page            error_page;
    std::list<c_location>   location;

};

std::ostream    &operator<<(std::ostream &o, c_server const &i);

#endif
