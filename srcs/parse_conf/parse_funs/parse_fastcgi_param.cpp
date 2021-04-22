#include "parse_conf.hpp"

void    parse_fastcgi_param(t_strcit it, void *ptr) {
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
int        main(void)
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
