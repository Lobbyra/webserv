#include "webserv.hpp"

volatile bool g_run = 1;

static void    set_reuse_port(t_socketlst const &lst) {
    int fd;
    const int opt = 1;
    t_socketlst::const_iterator it = lst.begin(), ite = lst.end();

    std::cout << "\r[STOP] Closing " << lst.size() << " sockets." << std::endl;
    for (; it != ite; ++it) {
        fd = it->entry_socket;

        if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)))
            ft_error("setsockopt");
        close(fd);
    }
}

void    webserv(std::list<c_server> const &conf) {
    t_respmap                       *resp_avail = new t_respmap;
    t_socketlst const               listen_ports = init_listen(conf);
    t_socketlst                     clients;
    std::list<s_request_header>     requests;

    while (g_run) {
        clients = ft_select(listen_ports, resp_avail);
        if (clients.empty() == false && g_run)
        {
            requests = parse_request(clients);
            // init_callback(clients, requests);
        }
    }
    set_reuse_port(listen_ports);
}
