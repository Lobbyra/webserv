#ifndef PARSE_CONF_HPP
# define PARSE_CONF_HPP

# include <list>
# include <string>
# include <iostream>
# include "../lib/lib.hpp"
# include "../utils/utils.hpp"
# include "../data_structures.hpp"

void            check_curly_braces(const std::string &conf);
std::string     get_conf(const char *const path);

std::string skip_k_get_value(const std::string &key,
        std::string::const_iterator &it, std::string const &sep);

void    parse_client_max_body_size(std::string::const_iterator it, void *ptr);
void    parse_root(std::string::const_iterator it, void *ptr);
void    parse_listen(std::string::const_iterator it, void *ptr);
void    parse_autoindex(std::string::const_iterator it, void *ptr);
void    parse_server_names(std::string::const_iterator it, void *ptr);
void    parse_fastcgi_param(std::string::const_iterator it, void *ptr);

void    skip_param(std::string::iterator &it);
void    skip_location(std::string::iterator &it);
void    skip_server(std::string::iterator &it,
                    std::string::iterator const &end);

// LIB FUNCTIONS FROM ./lib.cpp

#endif
