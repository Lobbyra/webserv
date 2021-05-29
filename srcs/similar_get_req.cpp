#include "webserv.hpp"

static bool    check_old_respons_is_valid(s_socket &client,
                                          s_similar_get_req *similar_req) {
    struct stat stat;

    errno = 0;
    if (client.ipport != similar_req->ipport)
        return (false);
    if (client.headers.host != similar_req->host)
        return (false);
    if (similar_req->last_state_change != stat.st_ctime)
        return (false);
    return (true);
}

void    similar_get_req_manager(t_socketlst *clients,
                                s_similar_get_req *similar_req) {
    struct stat                 stat;
    t_socketlst::iterator       it = clients->begin();
    t_socketlst::iterator       ite = clients->end();

    for (; it != ite; ++it) {
        if (lstat(similar_req->path_respons.c_str(), &stat) == -1)
            continue ;
        if (it->is_callback_created == false && it->is_write_ready == true &&
                it->headers.method == "GET" && it->headers.path == "/"     &&
                it->headers.error == 200                                   &&
                check_old_respons_is_valid((*it), similar_req) == true     &&
                it->ipport == similar_req->ipport                          &&
                it->headers.host == similar_req->host                      &&
                similar_req->last_state_change == stat.st_ctime) {
            if (send(it->client_fd, similar_req->respons.c_str(),
                        similar_req->respons.length(), 0) < 1) {
                std::cerr << "Error: Respons to client" << std::endl;
            }
            reset_socket(&(*it));
        }
    }
}