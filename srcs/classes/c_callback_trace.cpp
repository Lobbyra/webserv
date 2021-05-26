#include "c_callback.hpp"
extern bool g_verbose;

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
    std::string tmp;

    if (this->path == "")
        this->path = "/";
    tmp = this->method + " " + this->path + " " + this->protocol + "\n";
    if (write(_tmpfile->get_fd(), tmp.c_str(), tmp.size()) < 1) {
        std::cerr << "Error: write() in _write_request_line()" << std::endl;
    }
}

void                    c_callback::_read_client_to_tmpfile(void){
    if (g_verbose)
        std::cout << "TASK : _read_client_to_tmpfile()" << std::endl;
    char            *buf;
    int             bytes_read;
    bool            host;

    if (*(this->is_read_ready) == false) {
        _it_recipes--;
        return ;
    }
    _tmpfile = new c_tmpfile();
    host = false;
    _write_request_line();
    if (this->client_buffer->empty() == false) {
        buf = concate_list_str(this->client_buffer);
        bytes_read = ft_strlen(buf);
        write(_tmpfile->get_fd(), buf, bytes_read);
        if (_host_exist(buf) == true)
           host = true;
        free(buf);
    }
    if (host == false) {
        _recipes = _init_error_request();
        _it_recipes = _recipes.begin();
    }
    this->path = _tmpfile->get_filename();
    this->_resp_body = true;
    _continue();
}

std::list<c_callback::t_task_f>     c_callback::_init_recipe_trace(void) {
    std::list<t_task_f> tasks;

    tasks.push_back(&c_callback::_read_client_to_tmpfile);
    tasks.push_back(&c_callback::_gen_resp_headers);
    tasks.push_back(&c_callback::_read_body);
    tasks.push_back(&c_callback::_send_respons);
    tasks.push_back(&c_callback::_send_respons_body);
    return (tasks);
}
