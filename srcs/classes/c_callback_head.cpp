#include "c_callback.hpp"

std::string                         c_callback::_response(void) {
    std::stringstream sstr;
    std::string endl("\r\n");
    
    sstr << "HTTP/1.1 " << this->status_code << " "                 \
    << get_status_msg(this->status_code) << endl                   \
    << "Server: " << "Server Drunk Architect TEAM" << endl          \
    << "Date: " << "Mon, 27 Apr 1645 23:59:59 GMT" << endl << endl  \
    << "Body: Congragulation !" ;

    std::string       str = sstr.str();
    return (str);
}

void                                c_callback::_meth_head_request_is_valid(void) {
    this->path.insert(0, this->root);

    if ((open(this->path.c_str(), O_RDONLY)) == -1)
        this->status_code= 404;
    else
        this->status_code = 200;
}

void                                c_callback::_meth_head_send(void) {
    std::string     response = _response();
    std::cout << "Response: " << std::endl;
    std::cout << response.c_str() << std::endl;
    if (send(this->client_fd, response.c_str(), response.length(), 0) == -1) {
		std::cerr << "error: Respons to client" << std::endl;
	}
}

std::list<c_callback::t_task_f>     c_callback::_init_recipe_head(void) {
    std::list<t_task_f> tasks;

    tasks.push_back(&c_callback::_meth_head_request_is_valid);
    tasks.push_back(&c_callback::_meth_head_send);
    return (tasks);
}