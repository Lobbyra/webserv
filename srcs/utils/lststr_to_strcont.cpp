#include <list>
#include <string>
#include <iostream>

std::string lststr_to_strcont(std::list<std::string> const &lst,
                              std::string sep) {
    std::string concatenate;

    for (std::list<std::string>::const_iterator it = lst.begin();
            it != lst.end(); ++it) {
        concatenate += *it;
        concatenate += sep;
    }
    if (concatenate.size() > 0) {
        concatenate.erase(concatenate.size() - sep.size(), sep.size());
    }
    return (concatenate);
}

/*
int         main(int argc, char **argv) {
    std::string             tmp;
    std::list<std::string>  lst_one;
    std::list<std::string>  lst_two;
    std::list<std::string>  lst_three;

    if (argc != 2) {
        std::cerr << "bad args" << std::endl;
        return (1);
    }
    tmp = lststr_to_strcont(lst_one, argv[1]);
    std::cout << tmp << std::endl;

    lst_two.push_back("Salut");
    tmp = lststr_to_strcont(lst_two, argv[1]);
    std::cout << tmp << std::endl;

    lst_three.push_back("Salut");
    lst_three.push_back("mon");
    lst_three.push_back("pote");
    tmp = lststr_to_strcont(lst_three, argv[1]);
    std::cout << tmp << std::endl;
    return (0);
}
*/
