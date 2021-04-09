#ifndef PARSE_CLIENT_HPP
# define PARSE_CLIENT_HPP

#include "../webserv.hpp"

#include <unistd.h>
#include <list>

typedef void (*f_request_client)(char *line);

class c_request_client {
    public :

        std::string                 method;
        std::string                 path;
        std::string                 protocol;
        // date
        std::list<std::string>      accept_charset;
        std::list<std::string>      accept_language;
        std::list<std::string>      authorization;
        std::list<std::string>      content_language;
        std::string                 host;
        size_t                      port;
        std::string                 referer;
        std::list<std::string>      user_agent;
};


#endif