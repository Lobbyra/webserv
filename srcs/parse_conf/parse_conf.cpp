#include "parse_conf.hpp"

void    parse_conf(std::string str_conf) {
    std::string::iterator   it_conf = str_conf.begin();
    std::string::iterator   end_conf = str_conf.end();

    while (it_conf != str_conf.end()) {
        std::cout << std::string(it_conf, end_conf) << std::endl;
        skip_server(it_conf, end_conf);
    }
}

int         main(int argc, char **argv) {
    if (argc == 2)
        parse_conf(argv[1]);
    return (0);
}
