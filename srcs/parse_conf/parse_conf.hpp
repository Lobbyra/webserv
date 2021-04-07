#ifndef PARSE_CONF_HPP
# define PARSE_CONF_HPP

# include <list>
# include <string>
# include <iostream>
<<<<<<< HEAD
# include "lib.hpp"
=======
# include "../lib/lib.hpp"
# include "../data_structures.hpp"
>>>>>>> main

void    skip_param(std::string::iterator &it);
void    skip_location(std::string::iterator &it);
void    skip_server(std::string::iterator &it,
                    std::string::iterator const &end);

// LIB FUNCTIONS FROM ./lib.cpp

#endif
