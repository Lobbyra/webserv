#ifndef C_LOCATION_HPP
# define C_LOCATION_HPP

#include "../webserv.hpp"

class   c_server;

class    c_location {
 public:

    c_location(void);
    c_location(c_location const &src);
    c_location &operator=(c_location const &src);
    virtual ~c_location();

    int             client_max_body_size;
    t_strlst        index;
    t_strlst        methods;
    std::string     root;
    std::string     route;
    std::string     autoindex;
    std::string     fastcgi_pass;
    t_cgi_param     fastcgi_param;
    t_error_page    error_page;

};

std::ostream    &operator<<(std::ostream &o, c_location const &i);

#endif
