#include <string>
#include <stdlib.h>
#include <iostream>

/* STRCONT_TO_STR
 * This function transform a string container and alloc it in heap.
 */

char    *strcont_to_str(std::string str) {
    char *result;
    char *ptr_result;

    if (!(result = (char*)malloc(sizeof(char) * (str.size() + 1))))
        return (NULL);
    ptr_result = result;
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        *ptr_result = *it;
        ++ptr_result;
    }
    *ptr_result = '\0';
    return (result);
}

/*
int         main(int argc, char **argv) {
    char *str;

    if (argc != 2) {
        std::cout << "bad args" << std::endl;
        return (1);
    }
    str = strcont_to_str(argv[1]);
    std::cout << str << std::endl;
    free(str);
    return (0);
}
*/
