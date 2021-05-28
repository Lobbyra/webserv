#include "webserv.hpp"

static bool    check_old_respons_is_valid(s_socket client,
                    struct s_similar_get_req *similar_req) {
    struct stat         stat;

    if (lstat(similar_req->path_respons.c_str(), &stat) == -1)
        std::cerr << "Error: lstat check_old_respons_is_valid()" << std::endl;
    if (similar_req->last_state_change != stat.st_ctime)
        return (false);
    if (ft_strcmp(client.headers.host.c_str(), similar_req->host.c_str()) != 0)
        return (false);
    if (client.ipport != similar_req->ipport)
        return (false);
    return (true);
}

static void     send_same_request(s_socket *client,
                    struct s_similar_get_req *similar_req) {
    if (send(client->client_fd, similar_req->respons.c_str(),
        similar_req->respons.length(), 0) < 1) {
        std::cerr << "Error: Respons to client" << std::endl;
    }
    reset_socket(client);
}

void    similar_get_req_manager(t_socketlst *clients, struct s_similar_get_req *similar_req) {
    t_socketlst::iterator       it;
    t_socketlst::iterator       ite;

    it = clients->begin();
    ite = clients->end();
    for (; it != ite; ++it) {
        if ((*it).is_callback_created == false &&
            (*it).is_write_ready == true &&
            ft_strcmp((*it).headers.method.c_str(), "GET") == 0 &&
            ft_strcmp((*it).headers.path.c_str(), "/") == 0 &&
            ((*it).headers.error / 100 == 2)) {
                if (check_old_respons_is_valid((*it), similar_req) == true)
                    send_same_request(&(*it), similar_req);
        }
    }
}