#include "c_callback.hpp"
#include "read_headers.hpp"

extern bool g_verbose;

void                        c_callback::_check_is_body_to_large(void) {
    if (g_verbose)
        std::cout << "TASK : _check_is_body_to_large()" << std::endl;
    struct stat     stat;

    if (lstat(_tmpfile->get_filename().c_str(), &stat) != -1) {
        if (this->client_max_body_size != -1 &&
            stat.st_size > client_max_body_size) {
            this->status_code = 413;
        }
    }
}

void                       c_callback::_read_body_post(void) {
    if (g_verbose)
        std::cout << "TASK : _read_body_post()" << std::endl;
    int     buf_size;
    int     ret_read;
    char    buf[4096];
    char    *buffer;

    if (this->client_buffer->empty() == false) {
        buffer = cut_buffer_ret(this->client_buffer,
                                (int)this->content_length);
        _bytes_read = ft_strlen(buffer);
        free(buffer);
    }
    if (this->client_max_body_size != -1 &&
        _bytes_read > (int)this->client_max_body_size) {
        this->status_code = 413;
        return ;
    } else if (_bytes_read == (int)this->content_length)
        return ;
    if (this->content_length > 4096)
        buf_size = 4096;
    else
        buf_size = this->content_length;
    if (*this->is_read_ready == true) {
        if ((ret_read = read(client_fd, &buf, buf_size)) >= 1) {
            _bytes_read += ret_read;
            if (_bytes_read < (int)this->content_length)
                --_it_recipes;
            if (this->client_max_body_size != -1 &&
                    _bytes_read > (int)this->client_max_body_size) {
                    this->status_code = 413;
            return ;
            }
        }
        if (ret_read <= 0) {
            remove_client(this->clients, this->client_fd, 0);
            _exit();
        }
    }
}

void                       c_callback::_create_tmp_file(void) {
    if (g_verbose)
        std::cout << "TASK : _create_tmp_file()" << std::endl;
    char            buf[4096];
    int             status;

    if (_tmpfile == NULL)
        _tmpfile = new c_tmpfile();
    if (*this->is_read_ready == false)
        --_it_recipes;
    if ((status = read(client_fd, &buf, 4096)) >= 1) {
        write(_tmpfile->get_fd(), buf, status);
        --_it_recipes;
    }
}

std::list<c_callback::t_task_f>     c_callback::_init_recipe_post(void) {
    std::list<t_task_f>     tasks;

    if (this->transfer_encoding == "chunked") {
        tasks.push_back(&c_callback::_chunk_reading);
    } else {
        tasks.push_back(&c_callback::_create_tmp_file);
        tasks.push_back(&c_callback::_check_is_body_to_large);
        tasks.push_back(&c_callback::_read_body_post);
    }
    tasks.push_back(&c_callback::_gen_resp_headers);
    tasks.push_back(&c_callback::_send_respons);
    return tasks;
}
