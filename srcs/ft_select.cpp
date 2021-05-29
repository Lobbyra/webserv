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

/*
 * Returns:
 * 0: No new client/header ready
 * 1: New client
 * 2: New header ready to be read
 * 3: 1 & 2
 */
static int update_socketlst(t_socketlst *const lst, fd_set *r_set,
                             fd_set *w_set) {
    t_socketlst::iterator it = lst->begin(), ite = lst->end();
    bool isset_r, isset_w;
    int flag = 0;

    for (; it != ite; ++it) {
        isset_r = FD_ISSET(it->client_fd, r_set);
        isset_w = FD_ISSET(it->client_fd, w_set);

        it->is_read_ready = isset_r;
        it->is_write_ready = isset_w;
        if ((flag & 1) == false && FD_ISSET(it->entry_socket, r_set))
            flag |= 1;
        if ((flag & 2) == false && isset_r && it->is_header_read == false)
            flag |= 2;
    }
    return (flag);
}

/*
 * Return if a new header is ready to be read
 */
bool    ft_select(t_socketlst *const clients, struct s_similar_get_req *similar_req) {
    fd_set  r_fdset, w_fdset;
    struct timeval time = {2, 0};
    int     updated_flag;

    errno = 0;
    init_fdsets(clients, &r_fdset, &w_fdset);
    select(socket_max(clients) + 1, &r_fdset, &w_fdset, NULL, &time);
    updated_flag = update_socketlst(clients, &r_fdset, &w_fdset);

    if (errno == EAGAIN || errno == EINTR || (updated_flag & 1) == false) {
        // std::cout << "*silence*" << std::endl;
        errno = 0;
        return (updated_flag & 2);
    }
    else if (errno != 0)
        ft_error("select");
    if (clients->size() > 250) // Too much open fd protection
        return (updated_flag & 2);
    // ACCEPT NEW CLIENTS
    t_socketlst new_clients;
    t_socketlst::iterator it = clients->begin(), ite = clients->end();
    socklen_t   socklen = sizeof(sockaddr);
    for (; it != ite; ++it) {
        if (it->client_fd != 0 || FD_ISSET(it->entry_socket, &r_fdset) == false)
            continue ;
        s_socket nclient = *it;

        reset_socket(&nclient);
        nclient.client_fd = accept(nclient.entry_socket, \
                            &nclient.client_addr, &socklen);
        nclient.similar_req = similar_req;
        if (errno != 0)
            ft_error("accept");
        fcntl(nclient.client_fd, F_SETFL, O_NONBLOCK);
        new_clients.push_back(nclient);
    }
    clients->splice(clients->end(), new_clients);
    // std::cout << "*Toc toc toc*" << std::endl;
    return (updated_flag & 2);
}
