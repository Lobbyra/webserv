#include "c_callback.hpp"

std::list<c_callback::t_task_f>     c_callback::_init_recipe_post(void) {
    std::list<t_task_f>     tasks;

    tasks.push_back(&c_callback::_gen_resp_headers);
    tasks.push_back(&c_callback::_fd_is_ready_to_send);
    tasks.push_back(&c_callback::_send_respons);
    tasks.push_back(&c_callback::_send_respons_body);
    return tasks;
}
