#include "webserv.hpp"

#include <unistd.h>

volatile bool g_run = 1;

static void set_reuse_port(t_socketlst const *const lst) {
    int fd;
    const int opt = 1;
    t_socketlst::const_iterator it = lst->begin(), ite = lst->end();

    std::cout << "\r[STOP] Closing " << lst->size() << " sockets." << std::endl;
    for (; it != ite; ++it) {
        if (it->client_fd != 0)
            continue;
        fd = it->entry_socket;
        if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)))
            ft_error("setsockopt");
        if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
            ft_error("setsockopt");
        close(fd);
    }
}

static bool is_client_ready(t_socketlst const *const clients) {
    t_socketlst::const_iterator it = clients->begin(), ite = clients->end();

    for (; it != ite; ++it) {
        if (it->is_read_ready == true && it->is_header_read == false)
            return (true);
    }
    return (false);
}

void    webserv(std::list<c_server> const &conf) {
    t_socketlst                 *clients = new t_socketlst;
    std::list<s_request_header> requests;
    c_task_queue                task_queue;

    *clients = init_clients(conf);
    task_queue.set_clients(clients);
    while (g_run) {
        ft_select(clients);
        if (clients->size() > 1)
            std::cout << *clients << std::endl;
        if (g_run == false)
            break ;
        if (is_client_ready(clients) == true) {
            requests = parse_request(clients);
            assign_server_to_clients(conf, clients, requests);
            task_queue.push(requests, clients);
        }
        task_queue.exec_task();
        usleep(100);
    }
    set_reuse_port(clients);
    delete clients;
}
