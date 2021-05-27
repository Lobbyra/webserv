#include "parse_conf.hpp"

/* Expect "listen IP:PORT;"
 * Attached, no space allowed
 */

static void local_dns(std::string *str) {
    if (*str == "localhost")
        *str = "127.0.0.1";
}

void    parse_listen(std::string::const_iterator it, void *ptr) {
    s_ipport *const data = reinterpret_cast<s_ipport *>(ptr);
    std::string tmp = skip_k_get_value("listen", it, ";");
    const char *str = tmp.c_str();
    size_t colon;
    int i = 0;

    if (ft_isin(' ', tmp) ||
       (colon = tmp.find(':')) == std::string::npos)
        throw std::logic_error("Invalid listen");
    data->ip = std::string(str, str + colon);
    local_dns(&data->ip);
    str += colon + 1;
    data->port = ft_atoi_ptr(str, &i, false, false);

    if (i == 0 || str[i] != '\0' || data->ip.empty())
        throw std::logic_error("Invalid listen");
}

/*
int        main(void)
{
    s_ipport    res;
    std::string str = "listen 127.0.0.1:80; other_key other_value;";

    //str = "listen 127.0.0.1:80;";
    //str = "listen 127.0.0.1:80 other_key other_value;";
    //str = "listen;";
    //str = "listen 127.0.0.1:;";
    //str = "listen 127.0.0.1;";
    //str = "listen :80;";
    //str = "listen 80;";
    //str = "listen 127.0.0.1 :80;";
    //str = "listen 127.0.0.1: 80;";

    try {
        parse_listen(str.begin(), &res);
        std::cout << "IP: " << res.ip << " | PORT: " << res.port << std::endl;
    }
    catch(const std::exception &e) {
        std::cerr << "CATCH EXCEPTION: " << e.what() << std::endl;
    }
    std::cout << "Tried to parse: " << str << std::endl;
}
*/
