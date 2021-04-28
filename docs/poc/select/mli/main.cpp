#include "mini_server.hpp"

std::list<int> g_sockets;

int makeSocket(const int &port) {
    int newSocket;
    sockaddr_in servaddr;

    if ((newSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        ft_error("socket");
    g_sockets.push_back(newSocket);

    fcntl(newSocket, F_SETFL, O_NONBLOCK);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if ((bind(newSocket, (sockaddr *)&servaddr, sizeof(servaddr))) < 0)
        ft_error("bind");
    if ((listen(newSocket, 10)) < 0)
        ft_error("listen");
    return (newSocket);
}

std::ostream     &operator<<(std::ostream &o, std::list<int> const &lst) {
    if (lst.empty())
        return (o << "empty");

    std::list<int>::const_iterator it, ite = --lst.end();
    for (it = lst.begin(); it != ite; ++it)
        o << *it << " ";
    o << *it;
    return (o);
}

fd_set  fdset_full(void) {
    fd_set fdset;
    std::list<int>::const_iterator it, ite = g_sockets.end();

    FD_ZERO(&fdset);
    for (it = g_sockets.begin(); it != ite; ++it)
        FD_SET(*it, &fdset);
    return (fdset);
}

int socket_max(void) {
    std::list<int>::const_iterator it, ite = g_sockets.end();
    int max = 0;

    for (it = g_sockets.begin(); it != ite; ++it)
        if (*it > max)
            max = *it;
    return (max);
}

std::list<int>  ft_fd_isset(fd_set *fdset) {
    std::list<int> res;
    std::list<int>::const_iterator it, ite = g_sockets.end();

    for (it = g_sockets.begin(); it != ite; ++it)
        if (FD_ISSET(*it, fdset))
            res.push_back(*it);
    return (res);
}

#define STDIN STDIN_FILENO
#define BASE_VERBOSE 0
#define USE_STDIN 1
#define VERBOSE_STDIN 1

void    ft_server(std::list<int> ports)
{
    const std::string resp = "HTTP/1.1 200 OK\r\n\r\nGot The Message! :o";
    const int resp_len = strlen(resp.c_str());

    std::list<int>::const_iterator it, ite = ports.end();
    for (it = ports.begin(); it != ite; ++it)
        makeSocket(*it);

    std::cout << "Waiting connection on ports: " << ports << std::endl;
    while (true) {
        int     connfd;
        fd_set  fdset;
        struct timeval time;
        std::list<int> fd_isset;

        fdset = fdset_full();
        if (USE_STDIN)
            FD_SET(STDIN, &fdset);
        ft_timeout_init(&time);
        select(socket_max() + 1, &fdset, NULL, NULL, &time);

        fd_isset = ft_fd_isset(&fdset);

        if (USE_STDIN) {
            if (VERBOSE_STDIN)
                std::cout << "[A] IS_SET STDIN: " << FD_ISSET(STDIN, &fdset) << std::endl;
            if (FD_ISSET(STDIN, &fdset))
                fd_isset.push_back(STDIN);
        }

        if (errno == EAGAIN || fd_isset.size() == 0) {
            if (BASE_VERBOSE)
                std::cout << "No connection yet..." << std::endl;
            continue ;
        }
        else if (errno != 0)
            ft_error("select");

        std::list<int>::const_iterator it, ite = fd_isset.end();
        for (it = fd_isset.begin(); it != ite; ++it) {
            connfd = (*it == STDIN) ? STDIN : accept(*it, NULL, NULL);
            if (errno != 0)
                ft_error("accept");

            if (BASE_VERBOSE)
                std::cout << "Oh! Message received on socket: " << *it << std::endl;
            if (*it == STDIN) {
                char *line;
                std::cout << "GNL: " << get_next_line(connfd, &line) << std::endl;
                std::cout << "CONTENT: " << line << std::endl;
                free(line);
            }
            else {
                //read_fd(connfd);
                close(connfd);
            }
        }

        /*
        read_fd(connfd);
        if (write(connfd, resp.c_str(), resp_len) != resp_len)
            ft_error("write");
        */
    }
    (void)resp_len;
}

static bool usage_error(char *str)
{
    std::cout << "Usage:\n" << str << " <PORT> [PORT] [...]" << std::endl;
    return (1);
}

int main(int argc, char **argv) {
    std::list<int> ports;

    if (USE_STDIN == false && argc == 1)
        return (usage_error(argv[0]));
    for (int i = 1; i < argc; ++i)
        ports.push_back(atoi(argv[i]));

    ft_signalhandler_enable();
    ft_server(ports);
    return (0);
}
