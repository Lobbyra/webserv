#include "parse_conf.hpp"

void    parse_client_max_body_size(std::string::const_iterator it, void *ptr) {
    int         *data = (int *)ptr;
    std::string str = skip_k_get_value("client_max_body_size", it, ";");
    int i = 0;

    if (!ft_isdigit(str[i]))
        throw std::logic_error("Invalid client_max_body_size");
    *data = ft_atoi_ptr(str.c_str(), &i, false, false);
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
