#include "parse_conf.hpp"

bool    is_space(char c) {
    if (c == '\t' || c == '\n' || c == '\v' ||
        c == '\f' || c == '\r' || c == ' ')
        return (true);
    return (false);
}

std::list<std::string>  get_keys(void) {
    std::list<std::string>  keys;

    keys.push_back("root");
    keys.push_back("index");
    keys.push_back("listen");
    keys.push_back("location");
    keys.push_back("autoindex");
    keys.push_back("error_page");
    keys.push_back("server_name");
    keys.push_back("fastcgi_param");
    keys.push_back("client_max_body_size");
    return (keys);
}


