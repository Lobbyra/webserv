#include "c_callback.hpp"

void                        c_callback::_check_is_body_to_large(void) {
    struct stat     stat;

    if (lstat(_tmpfile->get_filename().c_str(), &stat) != -1) {
            if (this->client_max_body_size != -1 && 
                    stat.st_size > client_max_body_size)
                this->status_code = 413;
    }
}

void                        c_callback::_create_tmp_file(void) {
    char            *line;
    char            *tmp;
    int             status;

    if (this->client_max_body_size == -1)
        return ;
    if (*this->is_read_ready == false)
        --_it_recipes;
    if (_tmpfile == NULL)
        _tmpfile = new c_tmpfile();
    if ((status = get_next(client_fd, &line, "\r\n")) == 1) {
        tmp = ft_strjoin(line, "\r\n");
        write(_tmpfile->get_fd(), tmp, ft_strlen(tmp));
        free(tmp);
        free(line);
        --_it_recipes;
    }
    if (line != NULL)
        free(line);
}

std::list<c_callback::t_task_f>     c_callback::_init_recipe_post(void) {
    std::list<t_task_f>     tasks;

    if (this->transfer_encoding == "chunked") {
        tasks.push_back(&c_callback::_chunk_reading_size);
        tasks.push_back(&c_callback::_chunk_reading_chunk);
    } else {
        tasks.push_back(&c_callback::_create_tmp_file);
    }
    tasks.push_back(&c_callback::_check_is_body_to_large);
    tasks.push_back(&c_callback::_gen_resp_headers);
    tasks.push_back(&c_callback::_send_respons);
    return tasks;
}
