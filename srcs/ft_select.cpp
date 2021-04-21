#include <sys/select.h>
#include <sys/socket.h>
#include "utils/utils.hpp"

static void init_fdsets(t_socketlst *const lst, fd_set *r_set, fd_set *w_set) {
    t_socketlst::const_iterator it = lst->begin(), ite = lst->end();

    FD_ZERO(r_set);
    FD_ZERO(w_set);
    for (; it != ite; ++it) {
        FD_SET(it->entry_socket, r_set);
        if (it->client_fd != 0)
            FD_SET(it->client_fd, w_set);
    }
}

static int socket_max(t_socketlst *const lst) {
    t_socketlst::const_iterator it = lst->begin(), ite = lst->end();
    int max = -1;

    for (; it != ite; ++it) {
        if (it->entry_socket > max)
            max = it->entry_socket;
        if (it->client_fd > max)
            max = it->client_fd;
    }
    return (max);
}

static void update_socketlst(t_socketlst *const lst, fd_set *r_set, fd_set *w_set) {
    t_socketlst::iterator it = lst->begin(), ite = lst->end();

    for (; it != ite; ++it) {
        if (FD_ISSET(it->entry_socket, r_set))
            it->is_read_ready = true;
        if (FD_ISSET(it->client_fd, w_set))
            it->is_write_ready = true;
    }
}

void    ft_select(t_socketlst *const clients) {
    fd_set  r_fdset, w_fdset;
    struct timeval time;

    ft_timeval_init(&time, 1);
    init_fdsets(clients, &r_fdset, &w_fdset);
    select(socket_max(clients) + 1, &r_fdset, &w_fdset, NULL, &time);
    update_socketlst(clients, &r_fdset, &w_fdset);

    if (errno == EAGAIN || errno == EINTR || clients->size() == 0) {
        // Add if new_client
        // std::cout << "*silence*" << std::endl;
        return ;
    }
    else if (errno != 0)
        ft_error("select");

    t_socketlst::iterator it = clients->begin(), ite = clients->end();
    socklen_t   socklen = sizeof(t_sockaddr);
    for (; it != ite; ++it) {
        if (it->is_read_ready == false || it->client_fd != 0)
            continue ;
        it->client_fd = accept(it->entry_socket, &it->client_addr, &socklen);
        if (errno != 0)
            ft_error("accept");
    }
    std::cout << "*Toc toc toc*" << std::endl;
}
