#ifndef READ_HEADERS_HPP
# define READ_HEADERS_HPP

bool    flush_crlf(std::list<char*> *buffer);
bool    is_sep_header(std::list<char*> *buffer);

void    cut_buffer(std::list<char*> *buffer, unsigned int len);

char    *cut_buffer_ret(std::list<char*> *buffer, unsigned int len);

unsigned int find_str_buffer(std::list<char*> *buffer, std::string to_find);

#endif
