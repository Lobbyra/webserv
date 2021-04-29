#include <fcntl.h>      // open()
#include <dirent.h>     // opendir() & readdir()
#include <sys/stat.h>   // lstat()

#include "lib.hpp"      // ft_itoa() & ft_strcmp()

#include <string>
#include <iostream>

/* CREATE_CACHE_FILE
 * description :
 * This function will create a file intended to store a request and be deleted
 * after a response.
 *
 * where :
 * Files will be saved in CACHE_DIR/drunk_serv and this dir will be created
 * by this function if not exist.
 *
 * how :
 * Path of a cache file is CACHE_DIR/drunk_serv/[client_fd].req
 *
 * return :
 * This function return the fd of the cache file.
 */

#define CACHE_LOCATION "/tmp"
#define CACHE_NAME "cache_drunkserv"
#define CACHE_PATH CACHE_LOCATION "/" CACHE_NAME

#define CACHE_EXTENSION ".req"

#define DIR_DEFAULT_RIGHTS (S_IRWXU + S_IRGRP + S_IXGRP + S_IROTH + S_IXOTH)

static void print_err(std::string fun_failed) {
    std::cerr <<                                                          \
    "[" CACHE_PATH "] " << "create_cache_file failed : " << fun_failed << \
    " : " << strerror(errno) <<                                           \
    std::endl;
}

static bool is_cache_dir_exist(void) {
    int         status;
    DIR         *dir_cache_location;
    dirent      *it_dir;
    struct stat stat_curr_file;
    std::string str_it_full_path;

    errno = 0;
    if ((dir_cache_location = opendir(CACHE_LOCATION)) == NULL) {
        print_err("opendir()");
        return (false);
    }
    // Explore files in /tmp to find our cache directory
    while ((it_dir = readdir(dir_cache_location)) != NULL) {
        str_it_full_path = "";
        str_it_full_path += CACHE_LOCATION "/";
        str_it_full_path += it_dir->d_name;
        status = lstat(str_it_full_path.c_str(), &stat_curr_file);
        if (status == -1) {
            print_err("lstat()");
            return (true);
        }
        if (S_ISDIR(stat_curr_file.st_mode) == true &&
                ft_strcmp(it_dir->d_name, CACHE_NAME) == 0) {
            closedir(dir_cache_location);
            return (true);
        }
    }
    closedir(dir_cache_location);
    return (false);
}

// Return -1 mkdir fail, 0 else
static int create_cache_dir(void) {
    if (is_cache_dir_exist() == true) {
        std::cout <<                                                    \
        "[" CACHE_PATH "] " << "Request cache directory already exist." \
        << std::endl;
        return (0);
    }
    errno = 0;
    if (mkdir(CACHE_PATH, DIR_DEFAULT_RIGHTS) == -1) {
        print_err("mkdir()");
    } else {
        std::cout <<                                              \
        "[" CACHE_PATH "] " << "Request cache directory created." \
        << std::endl;
    }
    return (errno);
}

#define OFLAGS (O_RDWR | O_CREAT | O_TRUNC | O_NONBLOCK)

int     create_cache_file(int client_fd) {
    int         fd_cache;
    char        *str_client_fd;
    std::string path_cache;

    if (create_cache_dir() == -1) {
        return (-1);
    }
    if ((str_client_fd = ft_itoa(client_fd)) == NULL) {
        print_err("ft_itoa()");
        return(-1);
    }
    path_cache += CACHE_PATH "/";
    path_cache += str_client_fd;
    path_cache += CACHE_EXTENSION;
    fd_cache = open(path_cache.c_str(), OFLAGS, S_IRUSR | S_IWUSR);
    if (fd_cache == -1) {
        print_err("open()");
        return (-1);
    } else {
        std::cout << "[" << path_cache << "] Cache file created." << std::endl;
    }
    free(str_client_fd);
    return (fd_cache);
}

/*
int         main(void) {
    int fd;

    fd = create_cache_file(9);
    std::cout << "Cache file fd = " << fd << std::endl;
    if (fd != -1) {
        close(fd);
    }
    return (0);
}
*/
