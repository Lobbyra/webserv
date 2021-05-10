#include <iostream>

void    print_strs(char **strs, std::string sep) {
    if (strs == NULL)
        return ;
    while (*strs) {
        std::cout << *strs << sep << std::endl;
        ++strs;
    }
}
