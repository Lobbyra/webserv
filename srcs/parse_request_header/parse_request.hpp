#ifndef PARSE_REQUEST_HPP
# define PARSE_REQUEST_HPP

#include "../webserv.hpp"

#include <unistd.h>
#include <list>
#include <map>
#include <ostream>
#include <sstream>
 
typedef void (*f_request_header)(std::string line, void * p);

std::ostream& operator<<(std::ostream& os, s_request_header const &src);

s_request_header                 read_request_header(int fd);

std::list<std::string>           init_prefix_method(void);
std::map<std::string, void*>     init_request_header(s_request_header* request);
std::map<std::string, f_request_header>     init_parser_request(void);

void    parse_field_list_string(std::string line, void *p);
void    parse_field_std_string(std::string line, void *p);
void    parse_field_date(std::string line, void *p);
void    parse_field_size_t(std::string line, void *p);

void            parse_method(std::string line, 
                             std::map<std::string, void *> request_header);
void    parse_request_header(std::string line, 
                             std::map<std::string, void *> request_header,
                             std::map<std::string, f_request_header>
                             parser_request);

std::list<s_request_header>     parse_request(t_socketlst clients);

#endif