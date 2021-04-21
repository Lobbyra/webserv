#include "webserv.hpp"
#include <sys/socket.h>
#include <arpa/inet.h> // inet_pton
#include <fcntl.h>

static int  makeSocketfd(const int &port) {
    int newSocket;
    t_sockaddr_in servaddr;

    if ((newSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        ft_error("socket");

    fcntl(newSocket, F_SETFL, O_NONBLOCK);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if ((bind(newSocket, (t_sockaddr *)&servaddr, sizeof(servaddr))) < 0)
        ft_error("bind");
    if ((listen(newSocket, 10)) < 0)
        ft_error("listen");
    return (newSocket);
}

static s_socket makeSocket(const c_server *server) {
    s_socket newSocket;

    ft_bzero(&newSocket, sizeof(newSocket));
    newSocket.entry_socket = makeSocketfd(server->listen.port);
    newSocket.server = server;
    return (newSocket);
}

t_socketlst     init_clients(std::list<c_server> const &conf) {
    std::list<c_server>::const_iterator it = conf.begin(), ite = conf.end();
    t_socketlst res;

    for (; it != ite; ++it)
        res.push_back(makeSocket(&(*it)));
    return (res);
}
