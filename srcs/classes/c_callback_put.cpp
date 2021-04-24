#include "c_callback.hpp"

// Path, Host, Content-length

void                          c_callback::_meth_put_send(void) {
    std::string     response = _response();
    std::cout << "Response: " << std::endl;
    std::cout << response << std::endl;
    if (send(client_fd, response.c_str(), response.length(), 0) == -1) {
		std::cerr << "error: Respons to client" << std::endl;
	}
}

void        c_callback::_meth_put(void) {
    struct stat         stat;
    int                 file_fd;
    std::string         name_file(this->path);
    std::string         body_test("Body de test");
    this->path.insert(0, this->root);

    if (this->host.empty() == true)
        this->status_code = 400;
    if (lstat(this->path.c_str(), &stat) == 0) {
        this->status_code = 204;
    }
    if ((file_fd = open(name_file.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU)) != -1)
    {
        if (write(file_fd, body_test.c_str(), body_test.length()) != -1)
        {
            close(file_fd);
            this->status_code = 201;
            return ;
        }
        this->status_code = 500;
    }
}

std::list<c_callback::t_task_f>         c_callback::_init_recipe_put(void){
    std::list<t_task_f> tasks;

    tasks.push_back(&c_callback::_meth_put);
    tasks.push_back(&c_callback::_meth_put_send);
}