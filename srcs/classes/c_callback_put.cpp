#include "c_callback.hpp"

void                    c_callback::_meth_put_fd_is_ready_to_write(void) {
    if ( _fd_to_write.is_write_ready == false) {
        _it_recipes--;
    }
}

void        c_callback::_meth_put_open_fd(void) {
    struct stat         stat;
    int                 file_fd;
    this->path.insert(0, this->root);

    if (lstat(this->path.c_str(), &stat) == 0) {
        this->status_code = 204;
    }
    if ((file_fd = open(path.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU)) != -1) {
        s_socket tmp;

        tmp.entry_socket = 0;
        tmp.client_fd = file_fd;
        tmp.is_header_read = true;
        _fd_to_write = tmp;
        this->clients->push_back(tmp);
    }
}

void       c_callback::_meth_put_write_body(void) {
    std::string     body_test("Bonjour");

    if (write(_fd_to_write.client_fd, body_test.c_str(), body_test.length()) != -1) {
            close(_fd_to_write.client_fd);

            std::list<s_socket>::iterator   it = clients->begin();
            std::list<s_socket>::iterator   ite = clients->end();
            for (; it != ite; ++it) {
                if ((*it).client_fd == _fd_to_write.client_fd)
                    break ;
            }
            clients->erase(it);
            this->status_code = 201;
            return ;
        }
        this->status_code = 500;
}

std::list<c_callback::t_task_f>         c_callback::_init_recipe_put(void){
    std::list<t_task_f> tasks;

    tasks.push_back(&c_callback::_meth_put_open_fd);
    tasks.push_back(&c_callback::_gen_resp_headers);
    tasks.push_back(&c_callback::_meth_put_fd_is_ready_to_write);
    tasks.push_back(&c_callback::_meth_put_write_body);
    tasks.push_back(&c_callback::_fd_is_ready_to_send);
    tasks.push_back(&c_callback::_send_respons);
    return (tasks);
}