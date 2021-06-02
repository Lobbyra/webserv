#include "c_callback.hpp"

void                c_callback::_gen_resp_header_options(void) {
    char        *tmp = NULL;
    std::string str_methods;

    this->status_code = 200;
    _gen_resp_headers();
    size_t i = _resp_headers.find("\n");
    if (i != 0)
        i++;
    if (methods.empty() == false) {
        tmp = lststr_to_str(this->methods, ", ");
        str_methods = tmp;
        free(tmp);
    }
    str_methods.insert(0, "Allow: ");
    str_methods.insert(str_methods.length(), "\r\n");
    _resp_headers.insert(i, str_methods);
}


std::list<c_callback::t_task_f>        c_callback::_init_recipe_options(void) {
      std::list<t_task_f> tasks;

    tasks.push_back(&c_callback::_gen_resp_header_options);
    tasks.push_back(&c_callback::_read_body);
    tasks.push_back(&c_callback::_send_respons);
    tasks.push_back(&c_callback::_send_respons_body);
    return (tasks);
}
