#include "c_callback.hpp"
extern bool g_verbose;

std::string         c_callback::_find_index_if_exist(void) {
    std::list<std::string>::iterator    it, ite;
    std::string                         tmp_path = this->path;
    std::string::iterator               it_path;
    struct stat                         stat;

    it = this->index.begin();
    ite = this->index.end();
    it_path = tmp_path.end();
    if (*(--(tmp_path.end())) != '/')
        tmp_path.insert(tmp_path.end(), '/');
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
    if (g_verbose)
        std::cout << "TASK : _meth_get_request_is_valid" << std::endl;
    struct stat     stat;
    std::string     tmp_path;
    this->path.insert(0, this->root);

    if (this->method == "GET")                      // Response have header ?
        _resp_body = true;
    tmp_path = this->path;
    if (lstat(this->path.c_str(), &stat) == -1) {   // Path exist?
        this->status_code = 404;
    } else if ((stat.st_mode & S_IRUSR) == false) { // Do we have rights on it?
        if (g_verbose)
            std::cout << "Error: no reading rights" << std::endl;
        this->status_code = 403;
        this->content_length_h = 0;
    } else {                                        // Ok it exist and allowed
        if (S_ISDIR(stat.st_mode)) {
            this->path = _find_index_if_exist();
            if (this->path != tmp_path) {           // Index found
                return ;
            } else if (this->autoindex == "on") {   // Do we have autoindex ?
                _dir_listening_page = gen_listening(this->path);
                _resp_body = false;
                content_length_h = lststr_len(_dir_listening_page, "\r\n");
            } else {                                // No solution to get a dir
                this->status_code = 404;
            }
        } else {
            this->content_length_h = stat.st_size;
        }
    }
    _continue();
}

std::list<c_callback::t_task_f>     c_callback::_init_recipe_get(void) {
    std::list<t_task_f>     tasks;

    tasks.push_back(&c_callback::_meth_get_request_is_valid);
    tasks.push_back(&c_callback::_gen_resp_headers);
    tasks.push_back(&c_callback::_read_body);
    tasks.push_back(&c_callback::_send_respons);
    tasks.push_back(&c_callback::_send_respons_body);
    return tasks;
}
