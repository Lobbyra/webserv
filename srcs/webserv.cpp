#include "webserv.hpp"

void    webserv(std::list<c_server> const &conf) {
    t_respmap *resp_avail = new t_respmap;
    t_socketlst const listen_ports = init_listen(conf);
    t_socketlst clients;

    while (1) {
        clients = ft_select(listen_ports, resp_avail);
    }
}
