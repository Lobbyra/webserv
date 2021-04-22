#include <sys/select.h>
#include <sys/socket.h>
#include "utils/utils.hpp"

static void init_fdsets(t_socketlst const *lst, fd_set *r_set, fd_set *w_set) {
    t_socketlst::const_iterator it = lst->begin(), ite = lst->end();

    FD_ZERO(r_set);
    FD_ZERO(w_set);
    for (; it != ite; ++it) {
        FD_SET(it->entry_socket, r_set);
    }
}

static int socket_max(t_socketlst const *const lst) {
    t_socketlst::const_iterator it = lst->begin(), ite = lst->end();
    int max = -1;

    for (; it != ite; ++it) {
        if (it->entry_socket > max)
            max = it->entry_socket;
    }
    return (max);
}

static bool update_socketlst(t_socketlst *const lst, fd_set *r_set,
                             fd_set *w_set) {
    t_socketlst::iterator it = lst->begin(), ite = lst->end();
    bool raised_true = false;
    bool isset_r;

    // will be used to wait if client is ready to recieve the response 
    w_set = NULL;
    for (; it != ite; ++it) {
        isset_r = FD_ISSET(it->entry_socket, r_set);

        if (isset_r != it->is_read_ready)
            it->is_read_ready = isset_r;
        if (raised_true == false && isset_r)
            raised_true = true;
    }
    return (raised_true);
}

void    ft_select(t_socketlst *const clients) {
    fd_set  r_fdset, w_fdset;
    struct timeval time;
    bool    updated;

    ft_timeval_init(&time, 1);
    init_fdsets(clients, &r_fdset, &w_fdset);
    select(socket_max(clients) + 1, &r_fdset, &w_fdset, NULL, &time);
    updated = update_socketlst(clients, &r_fdset, &w_fdset);

    if (errno == EAGAIN || errno == EINTR || updated == false) {
        // std::cout << "*silence*" << std::endl;
        return ;
    }
    else if (errno != 0)
        ft_error("select");

    t_socketlst::iterator it = clients->begin(), ite = clients->end();
    socklen_t   socklen = sizeof(t_sockaddr);
    for (; it != ite; ++it) {
        if (it->is_read_ready == false)
            continue ;
        it->client_fd = accept(it->entry_socket, &it->client_addr, &socklen);
        if (errno != 0)
            ft_error("accept");
    }
    std::cout << "*Toc toc toc*" << std::endl;
}
