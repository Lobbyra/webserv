#include "c_callback.hpp"

void                                c_callback::_delete_request_is_valid(void) {
    DIR              *curr_directory = NULL;
    this->path.insert(0, this->root);

    if (this->host.empty() == true)
        this->status_code = 400;
    else if ((curr_directory = opendir(this->path.c_str())) == NULL) {
        this->status_code = 404;
        return ;
    }
    else
        this->status_code = 204;
    closedir(curr_directory);
}

void                          c_callback::_delete_response(void) {
    std::string     response = _response();
    std::cout << "Response: " << std::endl;
    std::cout << response << std::endl;
}

int                           c_callback::_remove_directory(const char *path)
{
    int                 ret;
    DIR                 *curr_directory;
    struct dirent       *it_directory;
    struct stat         stat;

    if ((curr_directory = opendir(path)) == NULL) {
        this->status_code = 404;
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
                _remove_directory(new_path.c_str());
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
            _remove_directory(this->path.c_str());
    }
}


std::list<c_callback::t_task_f>     c_callback::_init_recipe_delete(void) {
    std::list<t_task_f> tasks;

    tasks.push_back(&c_callback::_delete_request_is_valid);
    tasks.push_back(&c_callback::_delete_remove);
    tasks.push_back(&c_callback::_delete_response);
    return (tasks);
}