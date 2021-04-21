#include "parse_conf.hpp"

/*
 * This function have to parse a list of path. It throw and error only if
 * there isn't value between "index" and ';'.
 */

void    parse_index(std::string::const_iterator it, void *ptr) {
    std::list<std::string> *index = (std::list<std::string>*)ptr;

    it += ft_strlen("index ");
    if (*it == ';')
        throw std::logic_error("Empty value for key: index");
    while (*it != ';') {
        index->push_back(get_word_it(it, whitespaces + ";"));
        while (*it != ' ' && *it != ';')
            ++it;
        if (*it == ' ')
            ++it;
    }
}

/*
int         main(int argc, char **argv) {
    if (argc == 2) {
        std::string             str = argv[1];
        std::list<std::string>  strlist;

        parse_index(str.begin(), (void*)(&strlist));
        for (std::list<std::string>::iterator it = strlist.begin();
             it != strlist.end();
             it++) {
            std::cout << *it << std::endl;
        }
    }
    return (0);
}
*/
