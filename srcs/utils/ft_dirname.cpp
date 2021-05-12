#include <string>

/* FT_DIRNAME
 * This function is a reproduction of the real dirname in C++98.
 */

std::string ft_dirname(std::string const path) {
    std::string::const_iterator it_end = path.end();

    if (path.find("/") == std::string::npos)
        return (std::string("."));
    if (path == "/")
        return (std::string("/"));
    --it_end;
    while (*it_end == '/' && it_end != path.begin()) {
        --it_end;
    }
    while (it_end != path.begin()) {
        if (*it_end == '/') {
            break ;
        }
        --it_end;
    }
    return (std::string(path.begin(), it_end));
}

/* BASH TEST
#!/bin/bash

function test () {
    ./a.out $1
    dirname $1
    echo "----------"
}

a="/coucou/tmp/salut"
test $a
a="/coucou/tmp/salut/"
test $a
a="/"
test $a
./a.out ""
dirname ""
echo "----------"
a="coucou"
test $a
a="tmp/coucou/salut"
test $a
a="tmp/coucou/salut/"
test $a
*/

/*
#include <iostream>
int         main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "bad args" << std::endl;
        return (1);
    }
    std::cout << ft_basename(argv[1]) << std::endl;
    return (0);
}
*/
