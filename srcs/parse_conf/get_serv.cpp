#include "parse_conf.hpp"

/*
 * This function take a iterator on first letter of a server block. It will
 * create a server structure (s_server -> srcs/data_structures.hpp).
 * 
 * If a key word is not recognised, it will throw an error.
 * Same if a mandatory variable of the s_server isn't set by the context.
 */

void    get_serv(std::string::iterator it_conf) {
    std::string key;

    it_conf += ft_strlen("server { ");

    while (*it_conf != '}') {
        key = get_word_it(it_conf);
        std::cout << "key = " << key << std::endl;
        skip_param(it_conf);
    }
}

int         main(int argc, char **argv) {
    if (argc == 2) {
        std::string arg = argv[1];

        get_serv(arg.begin());
    }
    return (0);
}
