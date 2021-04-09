#include "../parse_conf.hpp"

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
