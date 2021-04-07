#include "parse_conf.hpp"

/*
 * This function will return a list of server blocks from the config file in
 * string in parameter.
 * 
 * This function is designed to be in a try-catch from parent code.
 * 
 * If a parsing on a key, a key is missing or if the parsing of a key isn't
 * correct (like index    ; -> value missing).
 */

void    parse_conf(std::string str_conf) {
    std::string::iterator   it_conf = str_conf.begin();
    std::string::iterator   end_conf = str_conf.end();

    while (it_conf != str_conf.end()) {
        std::cout << std::string(it_conf, end_conf) << std::endl;
        skip_server(it_conf, end_conf);
    }
}

int         main(int argc, char **argv) {
    if (argc == 2) {
        try {
            parse_conf(argv[1]);
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return (0);
}
