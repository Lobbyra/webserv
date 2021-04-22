#include "c_callback.hpp"

// check / suppression / response

void                                c_callback::_delete_request_is_valid(void) {
    if (this->host.empty() == false)
        this->status_code = 400;
    else if ((open(this->path.c_str(), O_RDONLY)) == -1)
        this->status_code= 404;
    else
        this->status_code = 204;
}


std::list<c_callback::t_task_f>     c_callback::_init_recipe_delete(void) {
    std::list<t_task_f> tasks;

    tasks.push_back(&c_callback::_delete_request_is_valid);
    return (tasks);