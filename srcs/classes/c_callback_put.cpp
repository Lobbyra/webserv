#include "c_callback.hpp"

#define PUT_OPEN_FLAGS (O_WRONLY | O_TRUNC)
#define PUT_OPEN_CREAT_FLAGS (O_WRONLY | O_TRUNC | O_CREAT)

void        c_callback::_meth_put_open_fd(void) {
    std::cout << "TASK : _meth_put_open_fd()" << std::endl;
    int         flags;
    mode_t      mode;
    struct stat stat;

    errno = 0;
    this->path.insert(0, this->root);
    if (lstat(this->path.c_str(), &stat) == 0 &&
            S_ISDIR(stat.st_mode) == false) {
        this->status_code = 204;
        flags = PUT_OPEN_FLAGS;
        mode = 0;
    } else if (S_ISDIR(stat.st_mode) == true) {
        this->status_code = 409;
        return ;
    } else {                                     // File does not exist
        this->status_code = 201;
        flags = PUT_OPEN_CREAT_FLAGS;
        mode = S_IRWXU;
    }
    if ((_fd_to_write = open(path.c_str(), flags, mode)) == -1) {
        std::cerr << "open() : " << strerror(errno) << std::endl;
        this->status_code = 500;
    }
}

void       c_callback::_meth_put_write_body(void) {
    std::cout << "TASK : _meth_put_write_body()" << std::endl;
    std::string     body_test("Bonjour ! Body testing.\nHappy test");

    if (is_fd_write_ready(_fd_to_write) == false) {
        _it_recipes--;
        return ;
    }
    if (write(_fd_to_write, body_test.c_str(), body_test.length()) == -1) {
        std::cerr << "write() : " << strerror(errno) << std::endl;
        this->status_code = 500;
    }
}

std::list<c_callback::t_task_f>         c_callback::_init_recipe_put(void){
    std::list<t_task_f> tasks;

    tasks.push_back(&c_callback::_meth_put_open_fd);
    tasks.push_back(&c_callback::_meth_put_write_body);
    tasks.push_back(&c_callback::_gen_resp_headers);
    tasks.push_back(&c_callback::_fd_is_ready_to_send);
    tasks.push_back(&c_callback::_send_respons);
    return (tasks);
}
