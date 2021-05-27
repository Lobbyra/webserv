#ifndef READ_HEADERS_HPP
# define READ_HEADERS_HPP

#include <map>
#include <string>
#include <list>

#include "s_request_header.hpp"

/* - HEADER PARSING FUNCTIONS -
 * Functions that will parse headers. Each will be called accord to the key
 * of the HTTP header.
 */
void    parse_field_date(std::string line, void *p);
void    parse_field_size_t(std::string line, void *p);
void    parse_field_std_string(std::string line, void *p);
void    parse_field_list_string(std::string line, void *p);

typedef void (*f_request_header)(std::string line, void * p);


std::map<std::string, void*>     init_header_ptrs(s_request_header* request);
std::map<std::string, f_request_header>     init_header_parsers(void);

void    parse_status_line(std::string line,
                          std::map<std::string, void*> *header_ptrs);
int     parse_header(std::string line,
                     std::map<std::string, void*> *header_ptrs,
                     std::map<std::string, f_request_header> *header_parsers);
/* -                          - */

/* - BUFFER MANAGMENT TOOLS -
 * Functions used to cut/flush/check buffer content/
 */
bool    flush_crlf(std::list<char*> *buffer);
bool    is_sep_header(std::list<char*> *buffer, bool is_status_line_read);

void    cut_buffer(std::list<char*> *buffer, unsigned int len);

char    *cut_buffer_ret(std::list<char*> *buffer, unsigned int len);

unsigned int find_str_buffer(std::list<char*> *buffer, std::string to_find);

std::string get_header(std::list<char*> *buffer, bool is_status_line_read);
/* -                        - */

#endif
