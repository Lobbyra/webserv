#include "c_callback.hpp"

bool                    c_callback::_if_error_page_exist(void) {
    std::cout << "TASK : _if_error_page_exist()" << std::endl;
    std::string                 path_error_page;
    t_error_page::iterator      it;
    struct stat                 stat;

    it = this->error_page.find(this->status_code);
    if (it != this->error_page.end()) {
        path_error_page.insert(0, (*it).second);
        if (lstat(path_error_page.c_str(), &stat) == 0)
            if (S_ISREG(stat.st_mode)) {
                this->path = path_error_page;
                this->content_length_h = stat.st_size;
                return (true);
            }
    }
    return (false);
}

void                    c_callback::_gen_error_header_and_body(void) {
    std::cout << "TASK : _gen_error_header_and_body()" << std::endl;

    if (_if_error_page_exist() == false) {
        std::string     tmp = get_err_page(this->status_code);
        this->content_length_h = tmp.length();
        _gen_resp_headers();
        _resp_headers.append(tmp);
        this->_resp_body = false;
    } else {
        _gen_resp_headers();
        this->_resp_body = true;
    }
}

std::list<c_callback::t_task_f>        c_callback::_init_error_request(void) {
    std::list<t_task_f> tasks;

    tasks.push_back(&c_callback::_gen_error_header_and_body);
    tasks.push_back(&c_callback::_fd_is_ready_to_send);
    tasks.push_back(&c_callback::_send_respons);
    return (tasks);
}
