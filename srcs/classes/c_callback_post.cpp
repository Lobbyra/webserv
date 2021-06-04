#include "c_callback.hpp"
#include "read_headers.hpp"

extern bool g_verbose;

void                       c_callback::_read_body_post(void) {
    if (g_verbose)
        std::cout << "TASK : _read_body_post()" << std::endl;
    int     buf_size;
    int     ret_read;
    char    buf[4096];
    char    *buffer;

    if (this->client_buffer->empty() == false) {
        buffer = cut_buffer_ret(this->client_buffer,
                (int)this->content_length, &(this->client->len_buf_parts));
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
        if ((ret_read = recv(client_fd, &buf, buf_size, 0)) >= 1) {
            _bytes_read += ret_read;
            if (_bytes_read < (int)this->content_length)
                --_it_recipes;
            if (this->client_max_body_size != -1 &&
                    _bytes_read > (int)this->client_max_body_size) {
                    this->status_code = 413;
            return ;
            }
        }
        if (ret_read == 0 || ret_read == -1) {
            std::cerr << "ERR: read_body_post : recv : " << ret_read << \
                std::endl;
            remove_client(this->clients, this->client_fd, 0);
            _exit();
            return ;
        }
    }
}

std::list<c_callback::t_task_f>     c_callback::_init_recipe_post(void) {
    std::list<t_task_f>     tasks;

    if (this->transfer_encoding == "chunked") {
        tasks.push_back(&c_callback::_chunk_reading);
    } else {
        tasks.push_back(&c_callback::_read_body_post);
    }
    tasks.push_back(&c_callback::_gen_resp_headers);
    tasks.push_back(&c_callback::_send_respons);
    return tasks;
}
