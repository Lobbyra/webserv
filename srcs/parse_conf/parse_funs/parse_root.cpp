#include "parse_conf.hpp"

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
