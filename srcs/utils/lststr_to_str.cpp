#include <list>
#include <string>

#include "utils.hpp"

char    *lststr_to_str(std::list<std::string> const &lst, std::string sep) {
    std::string concatenate;

    concatenate = "";
    for (std::list<std::string>::const_iterator it = lst.begin();
         it != lst.end(); ++it) {
        concatenate += *it;
        concatenate += sep;
    }
    if (concatenate.size() > 0)
        concatenate.erase(concatenate.end() - sep.size(), sep.end());
    return (strcont_to_str(concatenate));
}

/*
int         main(int argc, char **argv) {
    char        *tmp = NULL;
    std::list<std::string> lst_one;
    std::list<std::string> lst_two;
    std::list<std::string> lst_three;

    if (argc != 2) {
        std::cout << "bad args" << std::endl;
        return (1);
    }
    tmp = lststr_to_str(lst_one, argv[1]);
    std::cout << tmp << std::endl;
    free(tmp);

    lst_two.push_back("Salut");
    tmp = lststr_to_str(lst_two, argv[1]);
    std::cout << tmp << std::endl;
    free(tmp);

    lst_three.push_back("Salut");
    lst_three.push_back("mon");
    lst_three.push_back("pote");
    tmp = lststr_to_str(lst_three, argv[1]);
    std::cout << tmp << std::endl;
    free(tmp);
    return (0);
}
*/
