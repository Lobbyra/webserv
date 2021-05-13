#include "c_callback.hpp"

static bool             _host_exist(char *line) {
    std::string     prefix;
    std::string     tmp_line(line);
    std::string     sep(":");

    prefix = get_word(tmp_line, tmp_line.begin(), sep);
    if (prefix == "Host")
        return (true);
    return (false);
}

void                    c_callback::_write_request_line(void) {
    if (write(_tmpfile->get_fd(), this->method.c_str(),this->method.length())
        < 1) {
        std::cerr << "Error: write() in _write_request_line()" << std::endl;
    }
    if (write(_tmpfile->get_fd(), " ", 1) < 1) {
        std::cerr << "Error: write() in _write_request_line()" << std::endl;
    }
    if (write(_tmpfile->get_fd(), this->path.c_str(),this->path.length()) < 1) {
        std::cerr << "Error: write() in _write_request_line()" << std::endl;
    }
    if (write(_tmpfile->get_fd(), " ", 1) < 1) {
        std::cerr << "Error: write() in _write_request_line()" << std::endl;
    }
    if (write(_tmpfile->get_fd(), this->protocol.c_str(),
              this->protocol.length()) < 1) {
        std::cerr << "Error: write() in _write_request_line()" << std::endl;
    }
    if (write(_tmpfile->get_fd(), "\n", 1) < 1) {
        std::cerr << "Error: write() in _write_request_line()" << std::endl;
    }
}

void                    c_callback::_read_client_to_tmpfile(void){
    std::cout << "TASK : _read_client_to_tmpfile()" << std::endl;
    char            *line;
    char            *tmp;
    int             status;
    bool            host;

    host = false;
    _write_request_line();
    while ((status = get_next_line(client_fd, &line)) == 1) {
        if (line[0] == '\r')
            break ;
        tmp = ft_strjoin(line, "\n");
        write(_tmpfile->get_fd(), tmp, ft_strlen(tmp));
        if (_host_exist(line) == true)
           host = true;
        free(tmp);
        free(line);
    }
    if (line != NULL)
        free(line);
    if (host == false) {
        _recipes = _init_error_request();
        _it_recipes = _recipes.begin();
    }
    this->path = _tmpfile->get_filename();
    this->_resp_body = true;
}

std::list<c_callback::t_task_f>     c_callback::_init_recipe_trace(void) {
    std::list<t_task_f> tasks;

    _tmpfile = new c_tmpfile();
    tasks.push_back(&c_callback::_fd_is_ready_to_read);
    tasks.push_back(&c_callback::_read_client_to_tmpfile);
    tasks.push_back(&c_callback::_gen_resp_headers);
    tasks.push_back(&c_callback::_fd_is_ready_to_send);
    tasks.push_back(&c_callback::_send_respons);
    return (tasks);
}
