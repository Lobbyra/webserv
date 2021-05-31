#include "webserv.hpp"

extern bool g_verbose;

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

void    similar_get_req_sender(std::list<s_socket> *clients,
            s_similar_get_req *similar_req) {
    int         resp_len = similar_req->respons.length();
    char const  *resp = similar_req->respons.c_str();
    std::list<s_socket>::iterator it = clients->begin();
    std::list<s_socket>::iterator ite = clients->end();

    for (; it != ite; ++it) {
        if (it->is_cache_resp == false)
            continue ;
        if (g_verbose == true)
        std::cout << "LOG: cache_sender: " << \
            "[" << it->client_fd << "] : cache response" << std::endl;
        if (send(it->client_fd, resp, resp_len, 0) < 1) {
            std::cerr << "ERR: cache_sender: Respons to client" << std::endl;
        }
        reset_socket(&(*it));
    }
}

void    similar_get_req_checker(std::list<s_socket> *clients,
                                s_similar_get_req *similar_req) {
    struct stat                   stat;
    std::list<s_socket>::iterator it = clients->begin();
    std::list<s_socket>::iterator ite = clients->end();

    for (; it != ite; ++it) {
        if (lstat(similar_req->path_respons.c_str(), &stat) == -1 ||
                it->client_fd == 0 || it->is_header_read == false)
            continue ;
        if (it->is_callback_created == false && it->is_write_ready == true &&
                it->headers.method == "GET"                                &&
                it->headers.path == similar_req->original_path             &&
                it->headers.error == 200                                   &&
                check_old_respons_is_valid((*it), similar_req) == true     &&
                it->ipport == similar_req->ipport                          &&
                it->headers.host == similar_req->host                      &&
                similar_req->last_state_change == stat.st_ctime) {
            it->is_cache_resp = true;
        }
    }
}