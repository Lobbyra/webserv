#include "lib.hpp"

void        print_usage(void) {
    std::cout <<                          \
    "USAGE :" << std::endl <<             \
    "    ./select [PORT]" << std::endl << \
    "        [PORT] : Port to listen." << \
    std::endl;
}

int listen_fd;

void        signal_handler(int signum) {
    std::cout << "(" << signum << ") Serveur ending..." << std::endl;
    close(listen_fd);
    exit(1);
}

void        ft_select(int port) {
    // int listen_fd -> global;
    int                 client_fd = 0;
    fd_set              select_set;
    struct timeval      instant_timeout;
    struct sockaddr_in  listen_addr;

    signal(SIGINT, signal_handler);
    /*
     *  INIT LISTENING SOCKET
     */
    if ((listen_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "error: socket creation" << std::endl;
        exit(1);
    }

    listen_addr.sin_family = AF_INET;
    listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    listen_addr.sin_port = htons(port);

    fcntl(listen_fd, F_SETFL, O_NONBLOCK);

    if ((bind(listen_fd, (struct sockaddr *) &listen_addr, sizeof(listen_addr)))
            == -1) {
        std::cerr << "error: socket creation" << std::endl;
        exit(1);
    }

    if ((listen(listen_fd, 5)) == -1) {
        std::cerr << "error: listen call" << std::endl;
        exit(1);
    }

    /*
     * INIT FD SET
     */
    instant_timeout.tv_sec = 1;
    instant_timeout.tv_usec = 0;

    FD_ZERO(&select_set);
    int status = 0;
    while (1) {
        errno = 0;

        FD_SET(listen_fd, &select_set);
        // CHECK IF A CLIENT ACCEPTED
        status = select(listen_fd + 1,
                        &select_set, NULL, NULL,
                        &instant_timeout);
        if (status > 0 && FD_ISSET(listen_fd, &select_set)) {
            std::cout << "*toc toc*" << std::endl;
            if ((client_fd = accept(listen_fd, NULL, NULL)) == -1 &&
                EWOULDBLOCK != errno) {
                std::cerr << \
                "error: accept call : " << strerror(errno) << \
                std::endl;
                exit(1);
            }
        } else if (status == -1) {
            std::cerr << "select error" << std::endl;
            return;
        } else {
            std::cout << "*silence*" << std::endl;
        }

        // CLOSE CLIENT CONNECTION IF THERE WAS ONE
        if (client_fd > 0) {
            send(client_fd, "Who is it ?!\n", 13, 0);
            close(client_fd);
            client_fd = 0;
        }
    }

}

int         main(int argc, char **argv) {
    if (argc != 2) {
        print_usage();
        return (1);
    }
    ft_select(ft_atoi(argv[1]));
    return (0);
}
