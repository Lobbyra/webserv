#include "../parse_conf.hpp"

void    parse_fastcgi_pass(std::string::const_iterator it, void *ptr) {
    std::string *const data = reinterpret_cast<std::string *>(ptr);

    *data = skip_k_get_value("fastcgi_pass", it, ";");
    if (ft_isin(' ', *data))
        throw std::logic_error("Invalid fastcgi_pass");
}

/*
int        main(void)
{
    std::string res;
    std::string str = "fastcgi_pass path/to/file; other_key other_value;";

    // str = "fastcgi_pass /tmp/fastcgi.socket;";
    // str = "fastcgi_pass path/to/file other_key other_value;";
    // str = "fastcgi_pass;";

    try {
        parse_fastcgi_pass(str.begin(), &res);
        std::cout << "fastcgi_pass : |" << res << "|" << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "CATCH EXCEPTION: " << e.what() << std::endl;
    }
    std::cout << "Tried to parse: " << str << std::endl;
}
*/
