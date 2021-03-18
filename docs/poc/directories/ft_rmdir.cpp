/*
 * POC mkdir
 * 
 * USAGE
 * ./a.out [path to create a directory]
 */

#include <dirent.h>
#include <iostream>
#include <unistd.h>

void        print_usage(void) {
    std::cout << "USAGE :" << std::endl;
    std::cout << \
    "   ./ft_rmdir [path to create a directory]"
     << std::endl;
}

void        ft_rmdir(char *path) {
    if (rmdir(path) == -1) {
        std::cout << \
        "rmdir error: " << path << " " << strerror(errno) << \
        std::endl;
    } else {
        std::cout << path << " removed !" << std::endl;
    }
}

int         main(int argc, char **argv) {
    if (argc == 1 || argc > 2) {
        print_usage();
        return (1);
    }
    ft_rmdir(argv[1]);
    return (0);
}
