#include <sys/select.h>
#include <sys/socket.h>
#include "utils/utils.hpp"

fd_set  create_fdset(t_fdlst const &lst) {
    t_fdlst::const_iterator it = lst.begin(), ite = lst.end();
    fd_set fdset;

    FD_ZERO(&fdset);
    for (; it != ite; ++it)
        FD_SET(*it, &fdset);
    return (fdset);
}

std::list<int>  isset_to_lst(t_fdlst const &src, fd_set const *const fdset) {
    t_fdlst::const_iterator it = src.begin(), ite = src.end();
    t_fdlst res;

    for (; it != ite; ++it)
        if (FD_ISSET(*it, fdset))
            res.push_back(*it);
    return (res);
}

static void ft_timeout_init(struct timeval *const time) {
    ft_bzero(time, sizeof(*time));
    time->tv_sec = 1;
}

int socket_max(t_fdlst const &lst, std::map<int, bool> const *const map_) {
    int max = 0;

    t_fdlst::const_iterator it = lst.begin(), ite = lst.end();
    for (; it != ite; ++it)
        if (*it > max)
            max = *it;

    std::map<int, bool>::const_iterator m_it = map_->begin();
    std::map<int, bool>::const_iterator m_ite = map_->end();
    for (; m_it != m_ite; ++m_it)
        if (m_it->second == false && m_it->first > max)
            max = m_it->first;
    return (max);
}

std::list<s_client>
ft_select(t_fdlst const &listen_ports, std::map<int, bool> *resp_avail)
{
    fd_set  r_fdset;
    struct timeval time;
    std::list<int> fd_isset;
    std::list<s_client> clients;

    ft_timeout_init(&time);
    r_fdset = create_fdset(listen_ports);
    select(socket_max(listen_ports, resp_avail) + 1, &r_fdset, NULL, NULL, &time);

    fd_isset = isset_to_lst(listen_ports, &r_fdset);

    if (errno == EAGAIN || fd_isset.size() == 0) {
        std::cout << "No connection yet..." << std::endl;
        return (clients);
    }
    else if (errno != 0)
        ft_error("select");

    std::list<int>::const_iterator it, ite = fd_isset.end();
    for (it = fd_isset.begin(); it != ite; ++it) {
        s_client client;

        client.client_fd = accept(*it, NULL, NULL);
        clients.push_back(client); // Don't forget to link w/ server
        if (errno != 0)
            ft_error("accept");
        std::cout << "Oh! Message received on socket: " << *it << std::endl;
    }
    return (clients);
}
