#include "webserv.hpp"

#include <list>

#include <fcntl.h>
#include <arpa/inet.h> // inet_pton
#include <sys/socket.h>

#include "lib.hpp"
#include "c_server.hpp"
#include "s_socket.hpp"

static int  makeSocketfd(const int &port) {
    int newSocket;
    const int opt = 1;
    sockaddr_in servaddr;

    if ((newSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        ft_error("socket");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if (setsockopt(newSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
        ft_error("setsockopt");
    if ((bind(newSocket, (sockaddr *)&servaddr, sizeof(servaddr))) < 0)
        ft_error("bind");
    if ((listen(newSocket, 10)) < 0)
        ft_error("listen");
    return (newSocket);
}

static s_socket makeSocket(const c_server *server) {
    s_socket newSocket;

    newSocket.client_fd = 0;
    newSocket.entry_socket = 0;
    newSocket.is_read_ready = false;
    newSocket.is_write_ready = false;
    newSocket.is_callback_created = false;
    newSocket.is_status_line_read = false;
    newSocket.is_header_read = false;
    ft_bzero(&newSocket.client_addr, sizeof(sockaddr));
    newSocket.ipport = NULL;
    newSocket.server = NULL;
    newSocket.headers.error = 200;
    newSocket.headers.content_length = 0;
    newSocket.entry_socket = makeSocketfd(server->listen.port);
    newSocket.ipport = &server->listen;
    return (newSocket);
}

std::list<s_socket>     init_clients(std::list<c_server> const &conf) {
    std::list<s_socket> res;
    std::list<c_server>::const_iterator conf_it = conf.begin();
    std::list<c_server>::const_iterator conf_ite = conf.end();
    std::list<s_socket>::const_iterator sock_it;
    std::list<s_socket>::const_iterator sock_ite;

    for (; conf_it != conf_ite; ++conf_it) {
        if (conf_it->listen.ip.empty())
            continue ;
        sock_it = res.begin();
        sock_ite = res.end();
        while (sock_it != sock_ite && !(*sock_it->ipport == conf_it->listen))
            ++sock_it;
        if (sock_it != sock_ite) // Avoid duplicated sockets
            continue ;
        res.push_back(makeSocket(&(*conf_it)));
    }
    return (res);
}
