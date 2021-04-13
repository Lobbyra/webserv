#include "webserv.hpp"

void    webserv(std::list<c_server> const &conf) {
    std::map<int, bool> *resp_avail = new std::map<int, bool>;
    t_fdlst const listen_ports = init_listen(conf);
    std::list<s_client> clients;

    while (1) {
        clients = ft_select(listen_ports, resp_avail);
    }
}
