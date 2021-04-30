#include <sys/select.h>
#include <sys/socket.h>
#include <fcntl.h>

#include "lib.hpp"
#include "utils.hpp"
#include "std_typedefs.hpp"
#include "our_typedefs.hpp"

static void init_fdsets(t_socketlst const *lst, fd_set *r_set, fd_set *w_set) {
    t_socketlst::const_iterator it = lst->begin(), ite = lst->end();

    FD_ZERO(r_set);
    FD_ZERO(w_set);
    for (; it != ite; ++it) {
        if (it->client_fd == 0) {
            FD_SET(it->entry_socket, r_set);
            // FD_SET(it->entry_socket, w_set);
        } else {
            FD_SET(it->client_fd, r_set);
            FD_SET(it->client_fd, w_set);
        }
    }
}

static int socket_max(t_socketlst const *const lst) {
    t_socketlst::const_iterator it = lst->begin(), ite = lst->end();
    int max = -1;

    for (; it != ite; ++it) {
        if (it->client_fd == 0 && it->entry_socket > max)
            max = it->entry_socket;
        else if (it->client_fd != 0 && it->client_fd > max)
            max = it->client_fd;
    }
    return (max);
}

static bool update_socketlst(t_socketlst *const lst, fd_set *r_set,
                             fd_set *w_set) {
    t_socketlst::iterator it = lst->begin(), ite = lst->end();
    bool raised_true = false;
    bool isset_r, isset_w;

    for (; it != ite; ++it) {
        isset_r = FD_ISSET(it->entry_socket, r_set);
        isset_w = FD_ISSET(it->client_fd, w_set);

        it->is_read_ready = isset_r;
        it->is_write_ready = isset_w;
        if (FD_ISSET(it->client_fd, r_set))
            it->is_read_ready = true;
        if (raised_true == false && isset_r)
            raised_true = true;
    }
    return (raised_true);
}

static void ft_timeval_init(struct timeval *const time, int sec) {
    ft_bzero(time, sizeof(*time));
    time->tv_sec = sec;
}

void    ft_select(t_socketlst *const clients) {
    fd_set  r_fdset, w_fdset;
    struct timeval time;
    bool    updated_read;

    errno = 0;
    ft_timeval_init(&time, 1);
    init_fdsets(clients, &r_fdset, &w_fdset);
    select(socket_max(clients) + 1, &r_fdset, &w_fdset, NULL, &time);
    updated_read = update_socketlst(clients, &r_fdset, &w_fdset);

    if (errno == EAGAIN || errno == EINTR || updated_read == false) {
        // std::cout << "*silence*" << std::endl;
        return ;
    }
    else if (errno != 0)
        ft_error("select");

    if (clients->size() > 250) // Too much open fd protection
        return ;
    // Accept new clients and append it to the client list
    t_socketlst new_clients;
    t_socketlst::iterator it = clients->begin(), ite = clients->end();
    socklen_t   socklen = sizeof(sockaddr);
    for (; it != ite; ++it) {
        if (it->client_fd != 0 || it->is_read_ready == false)
            continue ;
        s_socket nclient = *it;

        nclient.client_fd = accept(nclient.entry_socket, \
                            &nclient.client_addr, &socklen);
        if (errno != 0)
            ft_error("accept");
        fcntl(nclient.client_fd, F_SETFL, O_NONBLOCK);
        new_clients.push_back(nclient);
    }
    clients->splice(clients->end(), new_clients);
    std::cout << "*Toc toc toc*" << std::endl;
}
