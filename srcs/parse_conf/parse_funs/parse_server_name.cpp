#include "../parse_conf.hpp"

void    parse_server_name(std::string::const_iterator it, void *ptr) {
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
        parse_server_name(str.begin(), &res);
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
