/*
 * POC mkdir
 * 
 * USAGE
 * ./a.out [path to create a directory]
 */

#include <iostream>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

#define DIR_DEFAULT_RIGHTS (S_IRWXU + S_IRGRP + S_IXGRP + S_IROTH + S_IXOTH)

void        print_usage(void) {
    std::cout << "USAGE :" << std::endl;
    std::cout << \
    "   ./ft_mkdir [path to create a directory]"
     << std::endl;
}

void        ft_mkdir(char *path) {
    errno = 0;

    if (mkdir(path, DIR_DEFAULT_RIGHTS) == -1) {
        std::cout << \
        "mkdir error: " << path << " " << strerror(errno) << \
        std::endl;
    } else {
        std::cout << path << " created !" << std::endl;
    }
}

int         main(int argc, char **argv) {
    if (argc == 1 || argc > 2) {
        print_usage();
        return (1);
    }
    ft_mkdir(argv[1]);
    return (0);
}
