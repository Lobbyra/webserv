#include <string>
#include <iostream>

/* FT_BASENAME
 * This function is a reproduction of the real basename in C++98.
 */

std::string ft_basename(std::string const path) {
    std::string::const_iterator it_start = path.end();
    std::string::const_iterator it_end = path.end();

    if (path.size() == 0)
        return (std::string(""));
    --it_start;
    while (*it_start == '/' && it_start != path.begin()) {
        it_end = it_start;
        --it_start;
    }
    while (it_start != path.begin()) {
        if (*it_start == '/') {
            ++it_start;
            break ;
        }
        --it_start;
    }
    return (std::string(it_start, it_end));
}

/*
int         main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "bad args" << std::endl;
        return (1);
    }
    std::cout << ft_basename(argv[1]) << std::endl;
    return (0);
}
*/
