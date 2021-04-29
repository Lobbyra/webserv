#include "c_callback.hpp"

void                c_callback::_gen_resp_header_options(void) {
    std::list<c_location>::iterator     it, ite;
    
    it = location.begin();
    ite = location.end();
    this->status_code = 200;
    _gen_resp_headers();
    size_t i = _resp_headers.find("\n");
    if (i != 0)
        i++;
    for (; it != ite; ++it)
        if ((*it).methods.empty() == false) 
            break ;
    std::string methods(lststr_to_str((*it).methods, ", "));
    methods.insert(0, "Allow: ");
    methods.insert(methods.length(), "\r\n");
    _resp_headers.insert(i, methods);
}


std::list<c_callback::t_task_f>        c_callback::_init_recipe_options(void) {
      std::list<t_task_f> tasks;

    tasks.push_back(&c_callback::_gen_resp_header_options);
    tasks.push_back(&c_callback::_fd_is_ready_to_send);
    tasks.push_back(&c_callback::_send_respons);
    return (tasks);
}