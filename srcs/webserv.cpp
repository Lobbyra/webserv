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
        if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) ||
            setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
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
    struct s_similar_get_req    similar_req;

    is_new_request = false;
    has_new_header_ready = false;
    clients = new t_socketlst;
    try {
        init_clients(conf, clients);
    }
    catch (std::exception const &e) {
        std::cerr << "init_clients: " << e.what() << std::endl;
        g_run = false;
    }
    task_queue.set_clients(clients);
    while (g_run) {
        has_new_header_ready = ft_select(clients, &similar_req);
        if (g_verbose && clients->size() > 1)
            std::cout << *clients << std::endl;
        if (g_run == false)
            break ;
        if (has_new_header_ready == true) {
            is_new_request = read_headers(clients);
            has_new_header_ready = false;
        }
        if (similar_req.host.empty() == false) {
           similar_get_req_manager(clients, &similar_req);
        }
        if (is_new_request == true) {
            for (std::list<s_socket>::iterator it = clients->begin();
                    it != clients->end(); ++it) {
                if (g_verbose == true && it->is_header_read == true &&
                        it->is_callback_created == false) {
                    std::cerr << "client : " << it->client_fd << std::endl;
                    std::cerr << it->headers << std::endl;
                }
            }
            assign_server_to_clients(conf, clients);
            task_queue.push(clients);
            is_new_request = false;
        }
        task_queue.exec_task();
    }
    set_reuse_port(clients);
    delete clients;
}
