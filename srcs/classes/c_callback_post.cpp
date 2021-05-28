#include "c_callback.hpp"

void                        c_callback::_check_is_body_to_large(void) {
    struct stat     stat;

    if (lstat(_tmpfile->get_filename().c_str(), &stat) != -1) {
            if (this->client_max_body_size != -1 &&
                    stat.st_size > client_max_body_size) {
                this->status_code = 413;
                }
    }
}

#define POST_BUF_SIZE 4096

/* _READ_BODY_POST
 * This function will flush the post body cause we don't care of a non-cgi
 * post body.
 */
void                       c_callback::_read_body_post(void) {
    int     buf_size;
    int     ret_read;
    char    *buf;

    if (this->content_length > POST_BUF_SIZE)
        buf_size = POST_BUF_SIZE;
    else
        buf_size = this->content_length;
    if (*this->is_read_ready == true) {
        if (!(buf = (char*)malloc(sizeof(char) * (buf_size)))) {
            this->status_code = 500;
            std::cerr << "error: _read_body_post: malloc failed" << std::endl;
            return ;
        }
        if ((ret_read = read(client_fd, &buf, buf_size)) >= 1) {
            _bytes_read += ret_read;
            if (_bytes_read < (int)this->content_length)
                --_it_recipes;
        }
        if (ret_read == 0 || ret_read == -1) {
            remove_client(this->clients, this->client_fd, ret_read);
            _exit();
        }
        free(buf);
    }
    return ;
}

void                       c_callback::_create_tmp_file(void) {
    char            buf[POST_BUF_SIZE];
    int             status;

    if (_tmpfile == NULL)
        _tmpfile = new c_tmpfile();
    if (*this->is_read_ready == false)
        --_it_recipes;
    if ((status = read(client_fd, &buf, POST_BUF_SIZE)) >= 1) {
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
