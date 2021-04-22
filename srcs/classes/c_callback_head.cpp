#include "c_callback.hpp"

// check valid | host exist | path exist

std::string                         c_callback::_response(void) {

}

void                                c_callback::_head_request_is_valid(void) {
    if (this->host.empty() == false)
        this->error = 400;
    else if ((open(this->path.c_str(), O_RDONLY)) == -1)
        this->error= 404;
    else
        this->error = 200;
}

void                                c_callback::_head_response(void) {
    std::string     response;


}

std::list<c_callback::t_task_f>     c_callback::_init_recipe_head(void) {
    std::list<t_task_f> tasks;

    tasks.push_back(&c_callback::_head_request_is_valid);


    return (tasks);
}