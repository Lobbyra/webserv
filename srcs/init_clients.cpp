#include "webserv.hpp"
#include <sys/socket.h>
#include <arpa/inet.h> // inet_pton
#include <fcntl.h>

static int  makeSocketfd(const int &port) {
    int newSocket;
    const int opt = 1;
    t_sockaddr_in servaddr;

    if ((newSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        ft_error("socket");

    fcntl(newSocket, F_SETFL, O_NONBLOCK);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if (setsockopt(newSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
        ft_error("setsockopt");
    if ((bind(newSocket, (t_sockaddr *)&servaddr, sizeof(servaddr))) < 0)
        ft_error("bind");
    if ((listen(newSocket, 10)) < 0)
        ft_error("listen");
    return (newSocket);
}

static s_socket makeSocket(t_socketlst const &socklst, const c_server *server) {
    t_socketlst::const_iterator it = socklst.begin(), ite = socklst.end();
    s_socket newSocket;

    while (it != ite && !(it->ipport->ip == server->listen.ip \
        && it->ipport->port == server->listen.port))
        ++it;
    if (it != ite)
        return (*it);
    ft_bzero(&newSocket, sizeof(newSocket));
    newSocket.entry_socket = makeSocketfd(server->listen.port);
    newSocket.ipport = &server->listen;
    return (newSocket);
}

t_socketlst     init_clients(std::list<c_server> const &conf) {
    std::list<c_server>::const_iterator it = conf.begin(), ite = conf.end();
    t_socketlst res;

    for (; it != ite; ++it)
        res.push_back(makeSocket(res, &(*it)));
    return (res);
}
