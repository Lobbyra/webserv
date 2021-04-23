
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

#include <dirent.h>

int         remove_directory(const char *path)
{
    int                 ret;
    DIR                 *curr_directory;
    struct dirent       *it_directory;
    struct stat         stat;

    if ((curr_directory = opendir(path)) == NULL) {
        std::cout << "Error: opendir" << std::endl;
        return (-1);
    }
    while ((it_directory = readdir(curr_directory)))
    {
        if (!strcmp(it_directory->d_name, ".") || !strcmp(it_directory->d_name, ".."))
             continue;
        std::string new_path(path);
        new_path.push_back('/');
        new_path.insert(new_path.size(), it_directory->d_name);
        if (!lstat(new_path.c_str(), &stat)) {
            if (S_ISREG(stat.st_mode))
                unlink(new_path.c_str());
            else if (S_ISDIR(stat.st_mode))
                remove_directory(new_path.c_str());
        }
    }
    closedir(curr_directory);
    ret = rmdir(path);
    return (ret);
}

int         main(int ac, char **av)
{
    if (ac != 2) {
        std::cout << "./program [folder]" << std::endl;
        return (-1);
    }
    struct stat         stat;

    if (!lstat(av[1], &stat)) {
            if (S_ISREG(stat.st_mode) || S_ISLNK(stat.st_mode))
                unlink(av[1]);
            else if (S_ISDIR(stat.st_mode))
                remove_directory(av[1]);
    }
    return (0);
}