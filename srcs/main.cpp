#include "webserv.hpp"

static int  print_usage(char *prog_name) {
    std::cerr << "Usage: " << prog_name << " <nginx.conf>" << std::endl;
    return (1);
}

int     main(int argc, char **argv) {
    if (argc != 2)
        return (print_usage(argv[0]));

    try {
        std::cout << parse_conf(argv[1]) << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << "Error config : " << e.what() << std::endl;
    }
    return (0);
}
