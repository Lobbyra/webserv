#include "parse_conf.hpp"

/*
 * This function take an iterator reference to the L of location and forward it
 * to the next key-word under server context.
 * 
 * Example :
 * 
 * input :
 * |
 * location { root coucou; index hey.html; } location { coucou }
 * 
 * output :
 *                                           |
 * location { root coucou; index hey.html; } location { coucou }
*/

void    skip_location(std::string::iterator &it) {
    while (*it != '}')
        ++it;
    ++it;
    while (is_space(*it))
        ++it;
}

/*
int         main(int argc, char **argv) {
    std::string arg(argv[1]);
    std::string::iterator it = arg.begin();

    std::cout << arg << std::endl;
    skip_location(it);

    std::string lo_skip(it, arg.end());
    std::cout << lo_skip << std::endl;
    return (0);
}
*/
