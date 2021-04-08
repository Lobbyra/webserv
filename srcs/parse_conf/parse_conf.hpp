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

void    skip_param(std::string::iterator &it);
void    skip_location(std::string::iterator &it);
void    skip_server(std::string::iterator &it,
                    std::string::iterator const &end);

// LIB FUNCTIONS FROM ./lib.cpp

#endif
