#include <string>
#include <iostream>

#include <stdlib.h>

/*
 * Prints an error and exit,
 * err = strerror(errno) by default
 */

void    ft_error(std::string const &src, std::string const &err) {
    std::cerr << src << ": " << err << std::endl;
    exit(1);
}
