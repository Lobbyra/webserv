#ifndef PARSE_REQUEST_HPP
# define PARSE_REQUEST_HPP

#include "../webserv.hpp"

#include <unistd.h>
#include <list>
#include <map>
#include <ostream>
 
typedef void (*f_request_header)(std::string line, 
                                 void * p);

class c_request_header {
    public :

        std::string                 method;
        std::string                 path;
        std::string                 protocol;
        std::string                 referer;
        std::string                 transfer_encoding;
        // date
        std::list<std::string>      accept_charset;
        std::list<std::string>      accept_language;
        std::list<std::string>      authorization;
        std::list<std::string>      content_type;
        std::list<std::string>      user_agent;
        std::string                 host;
        size_t                      port;
        size_t                      content_lenght;
        size_t                      error;
};

std::ostream& operator<<(std::ostream& os, c_request_header const &src);

std::list<std::string>           init_prefix_method(void);
std::map<std::string, void*>     init_request_header(c_request_header* request);
std::map<std::string, f_request_header>     init_parser_request(void);
void    parse_field_list_string(std::string line, 
                             void *p);

void            parse_method(std::string line, 
                             std::map<std::string, void *> request_header);
void    parse_request_header(std::string line, 
                             std::map<std::string, void *> request_header,
                             std::map<std::string, f_request_header>
                             parser_request);

#endif