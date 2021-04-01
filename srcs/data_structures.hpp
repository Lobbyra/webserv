#ifndef S_SERVER_HPP
# define S_SERVER_HPP

# include <map>
# include <list>
# include <vector>
# include <string>
# include <iostream>

struct              s_ipport {
    int             port;
    std::string     ip;
}

struct  s_location {
    int                         client_max_body_size;
    std::string                 root;
    std::string                 autoindex;
    std::list<std::string>      index;
    std::map<int, std::string>  error_page;
}

struct              s_server {
    int             client_max_body_size;
    std::string     root;
    s_ipport          listen;
    std::string
    std::styrin
}

#endif
