// POC opendir
//
// FUNCTIONS :
//      opendir, closedir, readdir, lstat
// 
// USAGE :
// ./ft_opendir [path you want to explore]

#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include <iostream>

void        print_usage(void) {
    std::cout << "USAGE :" << std::endl;
    std::cout << \
    "   ./ft_opendir [path you want to explore]"
     << std::endl;
}

void    print_err(const char *path, const char *called) {
    std::cout << \
    "error " << called << ": " << path << " " << strerror(errno) << \
    std::endl;
}

// Will print directory and subdirectories like tree binary.
void    ft_opendir(const char *path, int padding) {
    struct stat     stat_curr_file;
    DIR             *curr_dir;
    struct dirent   *it_dir;

    errno = 0;
    if ((curr_dir = opendir(path)) == NULL) {
        print_err(path, "opendir");
        return;
    }
    while ((it_dir = readdir(curr_dir))) {
        std::string str_padding(padding, ' ');
        std::string full_path_curr_file;

        // RECURSION CONDITION CREATION
        full_path_curr_file += path;
        full_path_curr_file += "/";
        full_path_curr_file += it_dir->d_name;
        if (strcmp(it_dir->d_name, ".") == 0 ||
            strcmp(it_dir->d_name, "..") == 0)
            continue;

        if ((lstat(full_path_curr_file.c_str(), &stat_curr_file)) == -1) {
            print_err(full_path_curr_file.c_str(), "lstat");
            return;
        }
        if (S_ISREG(stat_curr_file.st_mode) == false) {
            std::cout << str_padding << it_dir->d_name << "/" << std::endl;
            ft_opendir(full_path_curr_file.c_str(), padding + 4);
        } else {  // FILE PRINTING
            std::cout << str_padding << it_dir->d_name << std::endl;
        }
    }
}

int        main(int argc, char **argv) {
    if (argc == 1 || argc > 2) {
        print_usage();
        return (1);
    }
    ft_opendir(argv[1], 0);
    return (0);
    return (0);
}
