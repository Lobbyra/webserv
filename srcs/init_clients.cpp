#include "webserv.hpp"

#include <list>

#include <fcntl.h>
#include <arpa/inet.h> // inet_pton
#include <sys/socket.h>

#include "lib.hpp"
#include "c_server.hpp"
#include "s_socket.hpp"

static int  makeSocketfd(const s_ipport &ipport) {
    int newSocket;
    const int opt = 1;
    sockaddr_in servaddr;

    if ((newSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        throw std::logic_error("socket");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ipport.ip.c_str());
    servaddr.sin_port = htons(ipport.port);

    if (servaddr.sin_addr.s_addr == static_cast<in_addr_t>(-1))
        throw std::logic_error("inet_addr: Invalid IP");
    if (setsockopt(newSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
        throw std::logic_error("setsockopt");
    if ((bind(newSocket, (sockaddr *)&servaddr, sizeof(servaddr))) < 0)
        throw std::logic_error(std::string("bind: ") + strerror(errno));
    if ((listen(newSocket, 1000)) < 0)
        throw std::logic_error("listen");
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
    newSocket.entry_socket = makeSocketfd(server->listen);
    newSocket.ipport = &server->listen;
    return (newSocket);
}

void    init_clients(std::list<c_server> const &conf, t_socketlst *clients) {
    std::list<c_server>::const_iterator conf_it = conf.begin();
    std::list<c_server>::const_iterator conf_ite = conf.end();
    std::list<s_socket>::const_iterator sock_it;
    std::list<s_socket>::const_iterator sock_ite;

    for (; conf_it != conf_ite; ++conf_it) {
        if (conf_it->listen.ip.empty())
            continue ;
        sock_it = clients->begin();
        sock_ite = clients->end();
        while (sock_it != sock_ite && !(*sock_it->ipport == conf_it->listen))
            ++sock_it;
        if (sock_it != sock_ite) // Avoid duplicated sockets
            continue ;
        clients->push_back(makeSocket(&(*conf_it)));
    }
}
