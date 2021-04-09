#include "parse_conf.hpp"

/*
 * This function will return a list of server blocks from the config file in
 * string in parameter.
 * 
 * This function is designed to be in a try-catch from parent code.
 * 
 * If a parsing on a key, a key is missing or if the parsing of a key isn't
 * correct (like index    ; -> value missing).
 */

static void    skip_server(t_strcit &it,
                    std::string::iterator const &end) {
    int     curly_lvl = 0;

    while (!(*it == '}' && curly_lvl == 1) && it != end) {
        if (*it == '{')
            curly_lvl++;
        else if (*it == '}')
            curly_lvl--;
        ++it;
    }
    if (*it == '}')
        ++it;
    if (it != end)
        ++it;
}

std::list<c_server>     parse_conf(std::string path) {
    int                 server_id;
    t_strcit            it;
    std::string         conf;
    std::list<c_server> servers;

    server_id = 0;
    conf = get_conf(path.c_str());
    it = conf.begin();
    while (it != conf.end()) {
        servers.push_back(get_serv(it));
        servers.back().srv_id = server_id;
        skip_server(it, conf.end());
        ++server_id;
    }
    return (servers);
}

/*
int         main(int argc, char **argv) {
    if (argc == 2) {
        try {
            std::cout << parse_conf(argv[1]) << std::endl;
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return (0);
}
*/
