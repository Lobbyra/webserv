#include "parse_conf.hpp"

/*
 * This function take a iterator on first letter of a server block. It will
 * create a server structure (c_server -> srcs/data_structures.hpp).
 *
 * If a key word is not recognised, it will throw an error.
 * Same if a mandatory variable of the c_server isn't set by the context.
 */

#define SRV_KEY_NOT_CONTEXT "server: " + key + " not valid in location"
#define SRV_NOT_SERVER "server: " + key + " not a server block"

c_server    get_serv(t_strcit it_conf) {
    c_server    srv;
    std::string key;
    std::map<std::string, void*>    srv_ptr_select;
    std::map<std::string, f_parser> parse_select;

    parse_select = init_parsing_select();
    srv_ptr_select = init_srv_ptr_select(&srv);
    if ((key = get_word_it(it_conf)) != "server")
        throw std::logic_error(SRV_NOT_SERVER);
    else
        it_conf += ft_strlen("server { ");
    while (*it_conf != '}') {
        key = get_word_it(it_conf);
        check_key(key);
        if (key == "fastcgi_pass")
            throw std::logic_error(SRV_KEY_NOT_CONTEXT);
        parse_select[key](it_conf, srv_ptr_select[key]);
        skip_param(it_conf);
    }
    return (srv);
}

/*
int         main(int argc, char **argv) {
    if (argc == 2) {
        std::string conf = argv[1];

        try {
            c_server srv = get_serv(conf.begin());
            std::cout << srv;
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return (0);
}
*/
