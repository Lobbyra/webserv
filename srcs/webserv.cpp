#include "webserv.hpp"

volatile bool g_run = 1;

std::ostream    &operator<<(std::ostream &o, s_socket const &i) {
    o <<                                                                      \
    "entry_socket = " << i.entry_socket << std::endl <<                       \
    "client_fd = " << i.client_fd << std::endl <<                             \
    "is_read_ready = " << std::boolalpha << i.is_read_ready << std::endl <<   \
    "is_write_ready = " << std::boolalpha << i.is_write_ready << std::endl << \
    "is_header_read = " << std::boolalpha << i.is_header_read << std::endl << \
    std::endl;

    return (o);
}

static void set_reuse_port(t_socketlst const *const lst) {
    int fd;
    const int opt = 1;
    t_socketlst::const_iterator it = lst->begin(), ite = lst->end();

    std::cout << "\r[STOP] Closing " << lst->size() << " sockets." << std::endl;
    for (; it != ite; ++it) {
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
    while (g_run) {
        ft_select(clients);
        std::cout << *clients << std::endl;
        if (g_run == false)
            break ;
        if (is_client_ready(clients) == true) {
            requests = parse_request(clients);
            task_queue.push(requests, clients);
        }
        task_queue.exec_task();
    }
    set_reuse_port(clients);
    delete clients;
}
