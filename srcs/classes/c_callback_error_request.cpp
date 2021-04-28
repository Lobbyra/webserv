#include "c_callback.hpp"

void                    c_callback::_gen_error_header_and_body(void) {
    std::string     tmp = get_err_page(this->status_code);

    this->content_length_h = tmp.length();
    _gen_resp_headers();
    _resp_headers.append(tmp);
}

std::list<c_callback::t_task_f>        c_callback::_init_error_request(void) {
    std::list<t_task_f> tasks;

    tasks.push_back(&c_callback::_gen_error_header_and_body);
    tasks.push_back(&c_callback::_fd_is_ready_to_send);
    tasks.push_back(&c_callback::_send_respons);
    return (tasks);
}
