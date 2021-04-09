#include "utils.hpp"

/*
 * Forward it until a char in sep is encountered
 */

void    skip_it(std::string::const_iterator &it, const std::string sep) {
    while (sep.find(*it) == std::string::npos)
        ++it;
}
