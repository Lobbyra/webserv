# include "mini_serv.hpp"

void    print_usage(void) {
    std::cout << "MINI-SERV USAGE :" << std::endl;
    std::cout << "./mini-serv [PORT]" << std::endl;
    std::cout << "    [PORT] : number between 0-65535 is the port to listen. (don't use common port)" << std::endl;
}

int        main(int argc, char **argv) {
    if (argc != 2) {
        print_usage();
        return (1);
    }
    mini_serv(ft_atoi(argv[1]));
    return (0);
}
