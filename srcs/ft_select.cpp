#include <sys/select.h>
#include <sys/socket.h>
#include "utils/utils.hpp"

static fd_set  socketlst_to_fdset(t_socketlst const &lst) {
    t_socketlst::const_iterator it = lst.begin(), ite = lst.end();
    fd_set fdset;

    FD_ZERO(&fdset);
    for (; it != ite; ++it)
        FD_SET(it->entry_socket, &fdset);
    return (fdset);
}

static fd_set  respmap_to_fdset(t_respmap const *mp) {
    t_respmap::const_iterator it = mp->begin(), ite = mp->end();
    fd_set fdset;

    FD_ZERO(&fdset);
    for (; it != ite; ++it)
        if (it->second == false)
            FD_SET(it->first, &fdset);
    return (fdset);
}

static int socket_max(t_socketlst const &lst, t_respmap const *const map_) {
    int max = 0;

    t_socketlst::const_iterator it = lst.begin(), ite = lst.end();
    for (; it != ite; ++it)
        if (it->entry_socket > max)
            max = it->entry_socket;

    t_respmap::const_iterator m_it = map_->begin(), m_ite = map_->end();
    for (; m_it != m_ite; ++m_it)
        if (m_it->second == false && m_it->first > max)
            max = m_it->first;
    return (max);
}

static t_socketlst fdset_to_socklst(t_socketlst const &lst, fd_set const &set) {
    t_socketlst::const_iterator it = lst.begin(), ite = lst.end();
    t_socketlst res;

    for (; it != ite; ++it)
        if (FD_ISSET(it->entry_socket, &set))
            res.push_back(*it);
    return (res);
}

static void    fdset_to_respmap(t_respmap *mp, fd_set const &set) {
    t_respmap::iterator it = mp->begin(), ite = mp->end();

    for (; it != ite; ++it)
        if (it->second == false && FD_ISSET(it->first, &set))
            it->second = true;
}

t_socketlst ft_select(t_socketlst const &listen_ports, t_respmap *resp_avail)
{
    fd_set  r_fdset, w_fdset;
    struct timeval time;
    t_socketlst clients;

    ft_timeval_init(&time, 1);
    r_fdset = socketlst_to_fdset(listen_ports);
    w_fdset = respmap_to_fdset(resp_avail);
    select(socket_max(listen_ports, resp_avail) + 1, \
            &r_fdset, &w_fdset, NULL, &time);

    clients = fdset_to_socklst(listen_ports, r_fdset);
    fdset_to_respmap(resp_avail, w_fdset);

    if (errno == EAGAIN || clients.size() == 0) {
        std::cout << "*silence ...*" << std::endl;
        return (clients);
    }
    else if (errno != 0)
        ft_error("select");

    t_socketlst::iterator it = clients.begin(), ite = clients.end();
    socklen_t   socklen = sizeof(t_sockaddr);
    for (; it != ite; ++it) {
        it->client_fd = accept(it->entry_socket, &it->client_addr, &socklen);
        if (errno != 0)
            ft_error("accept");
    }
    std::cout << "*Toc toc toc*" << std::endl;
    return (clients);
}
