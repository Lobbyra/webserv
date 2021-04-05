#include "parse_conf.hpp"

/*
 * This function will take a string and will say if the string in a known
 * key-word.
 */

bool    is_key_known(std::string const &key) {
    std::list<std::string> keys = get_keys();

    if (ft_find(keys.begin(), keys.end(), key) == keys.end())
        return (false);
    return (true);
}

/*
int         main(int argc, char **argv) {
    std::cout << \
    std::boolalpha << is_key_known(argv[1]) << \
    std::endl;
    return (0);
}
*/
