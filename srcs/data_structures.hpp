#ifndef DATA_STRUCTURES_HPP
# define DATA_STRUCTURES_HPP

# include <map>
# include <list>
# include <vector>
# include <string>
# include <iostream>

typedef std::list<std::string> t_strlst;
typedef std::map<int, std::string> t_error_page;
typedef std::map<std::string, std::string> t_cgi_param;

struct  s_ipport {
    int             port;
    std::string     ip;
};

struct  s_location {
    int             client_max_body_size;
    std::string     root;
    std::string     autoindex;
    t_strlst        index;
    t_error_page    error_page;
    t_cgi_param     fastcgi_param;
};

struct  s_server {
    int             client_max_body_size;
    std::string     root;
    s_ipport        listen;
    std::string     autoindex;
    s_location      location;
    t_strlst        index;
    t_strlst        server_name;
    t_error_page    error_page;
    t_cgi_param     fastcgi_param;
};

#endif
