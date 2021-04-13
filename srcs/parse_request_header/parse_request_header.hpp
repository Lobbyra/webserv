#ifndef PARSE_HEADER_HPP
# define PARSE_HEADER_HPP

#include "../webserv.hpp"

#include <unistd.h>
#include <list>
#include <map>
#include <ostream>

typedef void (*f_request_header)(std::string line, 
                                 std::map<std::string, void *> request_header);

class c_request_header {
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
        size_t                      error;
};

std::ostream& operator<<(std::ostream& os, c_request_header const &src);

// init_maps.cpp
std::list<std::string>           init_prefix_method(void);
std::map<std::string, void*>     init_request_header(c_request_header* request);
std::map<std::string, f_request_header>     init_parser_request(void);

void            parse_method(std::string line, 
                             std::map<std::string, void *> request_header);

void    parse_request_header(std::string line, 
                             std::map<std::string, void *> request_header);

#endif