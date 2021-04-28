#include "webserv.hpp"

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

static bool is_client_ready(t_socketlst const *const sockets) {
    t_socketlst::const_iterator it = sockets->begin(), ite = sockets->end();

    for (; it != ite; ++it) {
        if (it->is_read_ready == true && it->is_header_read == false)
            return (true);
    }
    return (false);
}

void    webserv(std::list<c_server> const &conf) {
    t_socketlst                 *sockets;
    c_task_queue                task_queue;
    std::list<s_request_header> requests;

    sockets = new t_socketlst;
    *sockets = init_servers(conf);
    task_queue.set_clients(sockets);
    while (g_run) {
        ft_select(sockets);
        if (sockets->size() > 1)
            std::cout << *sockets << std::endl;
        if (g_run == false)
            break ;
        if (is_client_ready(sockets) == true) {
            requests = parse_request(sockets);
            assign_server_to_clients(conf, sockets, requests);
            task_queue.push(requests, sockets);
        }
        task_queue.exec_task();
    }
    set_reuse_port(sockets);
    delete sockets;
}
