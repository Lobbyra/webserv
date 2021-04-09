#include "parse_conf.hpp"

/*
 * This function will take a string and will say if the string in a known
 * key-word.
 */

void    check_key(std::string const &key) {
    std::list<std::string> keys = get_keys();

    if (ft_find(keys.begin(), keys.end(), key) == keys.end())
        throw std::logic_error(key + " key not known");
}

/*
int         main(int argc, char **argv) {
    std::cout << \
    std::boolalpha << check_key(argv[1]) << \
    std::endl;
    return (0);
}
*/
