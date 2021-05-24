#include <list>

#include "c_server.hpp"
#include "std_typedefs.hpp"
#include "our_typedefs.hpp"
#include "s_request_header.hpp"

/*
 * Assigns c_server* to clients
 * Server are chosen by s_ipport and server_name if match
*/

static bool is_right_conf(t_strlst const &serv_name,
            s_request_header const &request) {
    t_strlst::const_iterator s_it = serv_name.begin(), s_ite = serv_name.end();

    for (; s_it != s_ite; ++s_it) {
        if (*s_it == request.host)
            return (true);
    }
    return (false);
}

static c_server const *get_right_conf(std::list<c_server> const &conf,
        s_ipport const *const ipport, s_request_header const &request) {
    std::list<c_server>::const_reverse_iterator it_conf = conf.rbegin();
    std::list<c_server>::const_reverse_iterator ite_conf = conf.rend();
    std::list<c_server>::const_reverse_iterator right_conf;

    for (; it_conf != ite_conf; ++it_conf) {
        std::cout << "coucou" << std::endl;
        if (*ipport != it_conf->listen)
            continue ;
        right_conf = it_conf;
        if (is_right_conf(it_conf->server_name, request))
            break ;
    }
    return (&(*right_conf));
}

void    assign_server_to_clients(std::list<c_server> const &conf,
                                 t_socketlst *const clients) {
    std::list<s_socket>::iterator it_clients = clients->begin();
    std::list<s_socket>::iterator ite_clients = clients->end();

    while (it_clients != ite_clients) {
        if (it_clients->client_fd == 0 ||
                it_clients->is_callback_created == true) {
            ++it_clients;
            continue;
        }
        it_clients->server = get_right_conf(conf, it_clients->ipport,
                                            it_clients->headers);
        ++it_clients;
    }
}
