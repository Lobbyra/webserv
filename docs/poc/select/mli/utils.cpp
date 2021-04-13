#include "mini_server.hpp"

extern std::list<int> g_sockets;

void    ft_error(std::string const fct_name) {
    std::cout << fct_name << ": " << strerror(errno) << std::endl;
    exit(1);
}

void    ft_sigint(int sig) {
    int fd;
    int opt = 1;

    (void)sig;
    std::cout << \
        "\r[SIGINT] Closing " << g_sockets.size() << " sockets." << \
    std::endl;
    while (g_sockets.size() != 0) {
        fd = g_sockets.front();

        if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)))
            ft_error("setsockopt");
        close(fd);
        g_sockets.pop_front();
    }
    exit(0);
}

void    ft_signalhandler_enable(void) {
    signal(SIGINT, ft_sigint);
}

void    ft_signalhandler_disable(void) {
    signal(SIGINT, SIG_DFL);
}

void    read_fd(const int &fd) {
    int     n;
    char    *line;

    while ((n = get_next_line(fd, &line)) == 1) {
        std::cout << line << std::endl;
        free(line);
    }
    if (n == 0)
        free(line);
    else if (n == -1)
        ft_error("GNL");
}

void    ft_timeout_init(struct timeval *const time) {
    bzero(time, sizeof(*time));
    time->tv_sec = 1;
}
