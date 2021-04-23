#include "c_callback.hpp"

void                                c_callback::_delete_request_is_valid(void) {
    this->path.insert(0, root);

    if (this->host.empty() == true)
        this->status_code = 400;
    else if ((open(this->path.c_str(), O_RDONLY)) == -1)
        this->status_code= 404;
    else
        this->status_code = 204;
}

static int                          remove_directory(const char *path)
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
        if (!strcmp(it_directory->d_name, ".") ||
        !strcmp(it_directory->d_name, ".."))
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

void                                c_callback::_delete_remove(void) {
    struct stat         stat;

    if (!lstat(this->path.c_str(), &stat)) {
        if (S_ISREG(stat.st_mode) || S_ISLNK(stat.st_mode))
            unlink(this->path.c_str());
        else if (S_ISDIR(stat.st_mode))
            remove_directory(this->path.c_str());
    }
}


std::list<c_callback::t_task_f>     c_callback::_init_recipe_delete(void) {
    std::list<t_task_f> tasks;

    tasks.push_back(&c_callback::_delete_request_is_valid);
    tasks.push_back(&c_callback::_delete_remove);
    return (tasks);