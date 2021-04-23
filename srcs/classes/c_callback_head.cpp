#include "c_callback.hpp"

std::string                         c_callback::_response(void) {
    std::stringstream sstr;

    sstr << "HTTP/1.1 " << this->status_code << " "             \
    << _status_message[this->status_code] << std::endl          \
    << "Server: " << "Server Drunk Architect TEAM" << std::endl \
    << "Date: " << "Mon, 27 Apr 1645 23:59:59 GMT" << std::endl \
    << "Content-type: " << this->content_type << std::endl      \
    << "Content-length: " << std::endl;
    
    std::string       str = sstr.str();
    return (str);
}

void                                c_callback::_head_request_is_valid(void) {
    this->path.insert(0, root);

    if ((this->host.empty()) == true)
        this->status_code = 400;
    else if ((open(this->path.c_str(), O_RDONLY)) == -1)
        this->status_code= 404;
    else
        this->status_code = 200;
}

void                                c_callback::_head_response(void) {
    std::string     response = _response();
    std::cout << "Response: " << std::endl;
    std::cout << response << std::endl;
}

std::list<c_callback::t_task_f>     c_callback::_init_recipe_head(void) {
    std::list<t_task_f> tasks;

    tasks.push_back(&c_callback::_head_request_is_valid);
    tasks.push_back(&c_callback::_head_response);
    return (tasks);
}