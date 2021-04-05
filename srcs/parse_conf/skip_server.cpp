#include "parse_conf.hpp"

/*
 * This function will forward the iterator to the next server context or at the 
 * end of the string.
 * 
 * Exemple :
 */

void    skip_server(std::string::iterator &it,
                    std::string::iterator const &end) {
    int     curly_lvl = 0;

    while (!(*it == '}' && curly_lvl == 1) || it == end) {
        if (*it == '{')
            curly_lvl++;
        else if (*it == '}')
            curly_lvl--;
        ++it;
    }
    if (*it == '}') {
        ++it;
        while (is_space(*it))
            ++it;
    }
}

/*
int         main(int argc, char **argv) {
    std::string arg(argv[1]);
    std::string::iterator it = arg.begin();

    std::cout << arg << std::endl;
    skip_server(it, arg.end());

    std::string lo_skip(it, arg.end());
    std::cout << lo_skip << std::endl;
    return (0);
    return (0);
}
*/
