#include "c_callback.hpp"
extern bool g_verbose;

static bool             _host_exist(std::list<char*> *client_buffer) {
    int                             i = 0;
    int                             first_c = 0;
    int                             count = 0;
    std::list<char *>::iterator     it = client_buffer->begin();
    std::list<char *>::iterator     ite = client_buffer->end();

    while (it != ite) {
        while ((*it)[i]) {
            if ((*it)[i] == '\r' && (*it)[i + 1] == '\n') {
                if (ft_strncmp((*it) + first_c, "Host", 4) == 0)
                    count++;
                if ((*it)[i + 2] != '\0')
                    first_c = i + 2;
            }
            i++;
        }
        it++;
    }
    if (count == 1)
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

    if (_bytes_read == (int)this->content_length)
        return;
    if (*(this->is_read_ready) == false) {
        _it_recipes--;
        return ;
    }
    _tmpfile = new c_tmpfile();
    _write_request_line();
    if (this->client_buffer->empty() == false) {
        if (_host_exist(client_buffer) == true)
           _host = true;
        buf = concate_list_str(this->client_buffer);
        bytes_read = ft_strlen(buf);
        if (write(_tmpfile->get_fd(), buf, bytes_read) < 1)
            std::cerr << "error: _read_client_to_tmpfile | write()" <<std::endl;
        free(buf);
    }
    if (_host == false) {
        this->status_code = 400;
    } else {
        this->path = _tmpfile->get_filename();
        this->_resp_body = true;
    }
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
