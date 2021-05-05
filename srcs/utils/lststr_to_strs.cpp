#include <list>
#include <string>

#include "lib.hpp"

/* FT_PANIC
 * This function will decrease from curr to start to dealloc all strings.
 * It will free array of strings.
 */
static char **ft_panic(char **start, char **curr) {
    while (curr != start) {
        free(*curr);
        --curr;
    }
    free(start);
    return (NULL);
}

char    **lststr_to_strs(std::list<std::string> lst) {
    char **strs = NULL;
    char **i_strs = NULL;
    std::list<std::string>::iterator it = lst.begin();
    std::list<std::string>::iterator ite = lst.end();

    if (!(strs = (char**)malloc(sizeof(char*) * (lst.size() + 1))))
        return (NULL);
   i_strs = strs;
    while (it != ite) {
        if ((*i_strs = ft_strdup(it->c_str())) == NULL)
            return (ft_panic(strs, i_strs));
        ++it;
        ++i_strs;
    }
    *i_strs = NULL;
    return (strs);
}

/*
#include <iostream>
#include "utils.hpp"
int         main(void) {
    std::list<std::string> lst0; // EMPTY
    std::list<std::string> lst1; // ONE ELEM
    std::list<std::string> lst2; // SOME ELEMS
    std::list<std::string> lst3; // A LOT OF ELEMS
    char **tmp = NULL;

    std::cout << "lst0:" << std::endl;
    tmp = lststr_to_strs(lst0);
    print_strs(tmp, ", ");
    ft_freestrs(tmp);

    std::cout << "lst1:" << std::endl;
    lst1.push_back("one");
    tmp = lststr_to_strs(lst1);
    print_strs(tmp, ", ");
    ft_freestrs(tmp);

    std::cout << "lst2:" << std::endl;
    lst2.push_back("one");
    lst2.push_back("two");
    lst2.push_back("three");
    tmp = lststr_to_strs(lst2);
    print_strs(tmp, ", ");
    ft_freestrs(tmp);

    std::cout << "lst3:" << std::endl;
    lst3.push_back("one");
    lst3.push_back("two");
    lst3.push_back("three");
    lst3.push_back("four");
    lst3.push_back("five");
    lst3.push_back("six");
    lst3.push_back("seven");
    tmp = lststr_to_strs(lst3);
    print_strs(tmp, ", ");
    ft_freestrs(tmp);
    return (0);
}
*/
