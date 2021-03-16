#include "mini_client.hpp"

void    print_usage(void) {
    std::cout << "MINI-CLIENT USAGE :" << std::endl;
    std::cout << "./mini-client [IP] [PORT]" << std::endl;
    std::cout << "    [IP] : XXX.XXX.XXX.XXX" << std::endl;
    std::cout << "    [PORT] : number between 0-65535" << std::endl;
}

int     parsing(char *ip, char *port, net_dest *server) {
    if (inet_pton(AF_INET, ip, &(server->ip)) != 1) {
        std::cout << "error: inet_pton" << std::endl;
        return (1);
    }
    server->port = ft_atoi(port);
    return (0);
}

int     main(int argc, char **argv) {
    net_dest server;

    if (argc != 3 || parsing(argv[1], argv[2], &server) == 1) {
        print_usage();
        return(1);
    }
    mini_client(server);
    return (0);
}
