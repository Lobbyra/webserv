#include "getconf.hpp"
#include "../webserv.hpp"

static std::string skip_k_get_value(const std::string &key,
        std::string::const_iterator &it, std::string const &sep) {
    it += key.size();
    if (*it == ';')
        throw std::logic_error("Empty value for key: " + key);
    return (get_word_it(++it, sep));
}

void    parse_client_max_body_size(std::string::const_iterator it, void *ptr) {
    int *const data = reinterpret_cast<int *>(ptr);
    const char *str = skip_k_get_value("client_max_body_size", it, ";").c_str();
    int i = 0;

    if (!ft_isdigit(str[i]))
        throw std::logic_error("Invalid client_max_body_size");
    *data = ft_atoi_ptr(str, &i, false, false);
    if (str[i] == 'k')
        *data *= 1000;
    else if (str[i] == 'm')
        *data *= 1000000;
    else
        --i;
    ++i;
    if (str[i] != '\0')
        throw std::logic_error("Invalid client_max_body_size");
}

/*
int		main(void)
{
    int res;
    std::string str = "client_max_body_size 20m;";
    //str = "client_max_body_size m;";
    //str = "client_max_body_size;";
    //str = "client_max_body_size 2048;";
    //str = "client_max_body_size 2048t;";

    try {
        parse_client_max_body_size(str.begin(), &res);
        std::cout << "client_max_body_size : |" << res << "|" << std::endl;
    }
    catch(const std::exception &e) {
        std::cerr << "CATCH EXCEPTION: " << e.what() << std::endl;
    }
    std::cout << "Tried to parse: " << str << std::endl;
    return (0);
}
*/

void    parse_root(std::string::const_iterator it, void *ptr) {
    std::string *const data = reinterpret_cast<std::string *>(ptr);

    *data = skip_k_get_value("root", it, ";");
    if (ft_isin(' ', data->c_str()))
        throw std::logic_error("Invalid root");
}

/*
int		main(void)
{
    std::string res;
    std::string str = "root path/to/file; other_key other_value;";

    //str = "root path/to/file other_key other_value;";
    //str = "root;";

    try {
        parse_root(str.begin(), &res);
        std::cout << "root : |" << res << "|" << std::endl;
    }
    catch(const std::exception &e) {
        std::cerr << "CATCH EXCEPTION: " << e.what() << std::endl;
    }
    std::cout << "Tried to parse: " << str << std::endl;
}
*/

/* Expect "listen IP:PORT;"
 * Attached, no space allowed
 */

void    parse_listen(std::string::const_iterator it, void *ptr) {
    s_ipport *const data = reinterpret_cast<s_ipport *>(ptr);
    const char *str = skip_k_get_value("listen", it, ";").c_str();
    size_t colon;
    int i = 0;

    if (ft_isin(' ', str) ||
       (colon = std::string(str).find(':')) == std::string::npos)
        throw std::logic_error("Invalid listen");
    data->ip = std::string(str, str + colon);
    str += colon + 1;
    data->port = ft_atoi_ptr(str, &i, false, false);

    if (i == 0 || str[i] != '\0' || data->ip.empty())
        throw std::logic_error("Invalid listen");
}

/*
int		main(void)
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

void    parse_autoindex(std::string::const_iterator it, void *ptr) {
    std::string *const data = reinterpret_cast<std::string *>(ptr);

    *data = skip_k_get_value("autoindex", it, ";");
    if (data->compare("off") && data->compare("on"))
        throw std::logic_error("Invalid autoindex");
}

/*
int		main(void)
{
    std::string res;
    std::string str = "autoindex on;";

    //str = "autoindex on; other_key other_value;";
    //str = "autoindex on other_key other_value;";
    //str = "autoindex;";
    //str = "autoindex off;";
    //str = "autoindex offe;";
    //str = "autoindex om;";

    try {
        parse_autoindex(str.begin(), &res);
        std::cout << "autoindex : |" << res << "|" << std::endl;
    }
    catch(const std::exception &e) {
        std::cerr << "CATCH EXCEPTION: " << e.what() << std::endl;
    }
    std::cout << "Tried to parse: " << str << std::endl;
}
*/

void    parse_server_names(std::string::const_iterator it, void *ptr) {
    t_strlst *const data = reinterpret_cast<t_strlst *>(ptr);
    std::string str = skip_k_get_value("server_name", it, ";");
    size_t pos = 0, next_space;

    while ((next_space = str.find(' ', pos)) != std::string::npos) {
        data->push_back(str.substr(pos, next_space - pos));
        pos = next_space + 1;
    }
    data->push_back(str.substr(pos, std::string::npos));
}

/*
int		main(void)
{
    t_strlst res;
    std::string str = "server_name example.xd www.example.org; other_key other_value;";

    //str = "server_name example.lol; other_key other_value;";
    //str = "server_name example.org other_key other_value;";
    //str = "server_name;";
    //str = "server_name example.org google.fr website.lmao heyho.com;";

    try {
        parse_server_names(str.begin(), &res);
        t_strlst::const_iterator it = res.begin(), ite = res.end();
        for (; it != ite; ++it)
            std::cout << "server_name : |" << *it << "|" << std::endl;
    }
    catch(const std::exception &e) {
        std::cerr << "CATCH EXCEPTION: " << e.what() << std::endl;
    }
    std::cout << "Tried to parse: " << str << std::endl;
}
*/

void    parse_fastcgi_param(std::string::const_iterator it, void *ptr) {
    t_cgi_param *const data = reinterpret_cast<t_cgi_param *>(ptr);
    std::string str = skip_k_get_value("fastcgi_param", it, ";");
    std::string key, value;
    size_t sep;

    if ((sep = str.find(' ')) == std::string::npos)
        throw std::logic_error("Invalid fastcgi_param");
    if (str.find(' ', sep + 1) != std::string::npos)
        throw std::logic_error("Invalid fastcgi_param");
    key = str.substr(0, sep);
    value = str.substr(sep + 1, std::string::npos);
    if (data->insert(t_cgi_param::value_type(key, value)).second == false)
        throw std::logic_error("fastcgi_param key already exist");
}

/*
int		main(void)
{
    t_cgi_param res;
    std::string str = "fastcgi_param example.xd test;";

    //str = "fastcgi_param SCRIPT_FILENAME /home/www/scripts/php$fastcgi_script_name;";
    //str = "fastcgi_param QUERY_STRING $query_string;";
    //str = "fastcgi_param REQUEST_METHOD $request_method;";
    //str = "fastcgi_param CONTENT_TYPE $content_type;";
    //str = "fastcgi_param CONTENT_LENGTH $content_length;";
    //str = "fastcgi_param example.lol; other_key other_value;";
    //str = "fastcgi_param example.org other_key other_value;";
    //str = "fastcgi_param example.org google.fr website.lmao heyho.com;";
    //str = "fastcgi_param;";

    try {
        parse_fastcgi_param(str.begin(), &res);
        t_cgi_param::const_iterator it = res.begin(), ite = res.end();
        for (; it != ite; ++it)
            std::cout << "fastcgi_param : " << it->first << " | " \
                << it->second << std::endl;
    }
    catch(const std::exception &e) {
        std::cerr << "CATCH EXCEPTION: " << e.what() << std::endl;
    }
    std::cout << "Tried to parse: " << str << std::endl;
}
*/
