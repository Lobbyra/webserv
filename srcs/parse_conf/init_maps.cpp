#include "parse_conf.hpp"

std::map<std::string, f_parser> init_parsing_select(void) {
    std::map<std::string, f_parser> m;

    m["root"] = &parse_root;
    m["index"] = &parse_index;
    m["listen"] = &parse_listen;
    m["autoindex"] = &parse_autoindex;
    m["error_page"] = &parse_error_page;
    m["server_name"] = &parse_server_name;
    m["client_max_body_size"] = &parse_client_max_body_size;
    return (m);
}

std::map<std::string, void*>    init_srv_ptr_select(c_server *srv) {
    std::map<std::string, void*> m;

    m["root"] = &(srv->root);
    m["index"] = &(srv->index);
    m["listen"] = &(srv->listen);
    m["autoindex"] = &(srv->autoindex);
    m["error_page"] = &(srv->error_page);
    m["server_name"] = &(srv->server_name);
    m["client_max_body_size"] = &(srv->client_max_body_size);
    return (m);
}

std::map<std::string, void*>    init_loc_ptr_select(c_location *loc) {
    std::map<std::string, void*> m;

    m["root"] = &(loc->root);
    m["index"] = &(loc->index);
    m["autoindex"] = &(loc->autoindex);
    m["error_page"] = &(loc->error_page);
    m["client_max_body_size"] = &(loc->client_max_body_size);
    return (m);
}
