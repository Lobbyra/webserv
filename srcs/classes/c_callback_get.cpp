#include "c_callback.hpp"

std::string         c_callback::_find_index_if_exist(void) {
    std::list<std::string>::iterator    it, ite;
    std::string                         tmp_path = this->path;
    std::string::iterator               it_path;
    struct stat                         stat;

    it = this->index.begin();
    ite = this->index.end();
    it_path = tmp_path.end();
    for (; it != ite ; ++it)
    {
        tmp_path.insert(tmp_path.length(), *it);
        if (lstat(tmp_path.c_str(), &stat) == 0) {
            this->content_length_h = stat.st_size;
            break ;
        }
        tmp_path = this->path;
    }
    return (tmp_path);
}

void                c_callback::_meth_get_request_is_valid(void) {
    std::cout << "TASK : _meth_get_request_is_valid" << std::endl;
    struct stat     stat;
    std::string     tmp_path;
    this->path.insert(0, this->root);

    if (this->method == "GET")
        this->_resp_body = true;
    tmp_path = this->path;
    if (lstat(this->path.c_str(), &stat) == -1) {
        this->status_code = 404;
    } else if ((stat.st_mode & S_IRUSR) == false) {
        std::cout << "Error: no reading rights" << std::endl;
        this->status_code = 403;
        this->content_length_h = 0;
    } else {
        this->status_code = 200;
        this->content_length_h = stat.st_size;
        if (S_ISDIR(stat.st_mode) && this->index.empty() == false)
            if ((this->path = _find_index_if_exist()) == tmp_path) {
                this->status_code = 403;
                this->content_length_h = 0;
        }
    }
}

std::list<c_callback::t_task_f>     c_callback::_init_recipe_get(void) {
    std::list<t_task_f>     tasks;

    tasks.push_back(&c_callback::_meth_get_request_is_valid);
    tasks.push_back(&c_callback::_gen_resp_headers);
    tasks.push_back(&c_callback::_fd_is_ready_to_send);
    tasks.push_back(&c_callback::_send_respons);
    return tasks;
}