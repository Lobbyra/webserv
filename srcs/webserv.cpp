#include "webserv.hpp"

#include <unistd.h>

volatile bool g_run = 1;
bool g_verbose = false;

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

void    webserv(std::list<c_server> const &conf) {
    bool                        is_new_request;
    bool                        has_new_header_ready;
    t_socketlst                 *clients;
    c_task_queue                task_queue;
    std::list<s_request_header> requests;

    is_new_request = false;
    has_new_header_ready = false;
    clients = new t_socketlst;
    *clients = init_clients(conf);
    task_queue.set_clients(clients);
    while (g_run) {
        has_new_header_ready = ft_select(clients);
        std::cout << "1" << std::endl;
        if (g_verbose && clients->size() > 1)
            std::cout << *clients << std::endl;
        if (g_run == false)
            break ;
        if (has_new_header_ready == true) {
            std::cout << "2" << std::endl;
            is_new_request = read_headers(clients);
            std::cout << "3" << std::endl;
            has_new_header_ready = false;
        }
        if (is_new_request == true) {
            for (std::list<s_socket>::iterator it = clients->begin();
                    it != clients->end(); ++it) {
                if (it->is_header_read == true) {
                    std::cout << it->headers << std::endl;
                }
            }
            std::cout << "4" << std::endl;
            assign_server_to_clients(conf, clients);
            std::cout << "5" << std::endl;
            task_queue.push(clients);
            std::cout << "6" << std::endl;
            is_new_request = false;
        }
        else
            task_queue.exec_task();
    }
    set_reuse_port(clients);
    delete clients;
}
