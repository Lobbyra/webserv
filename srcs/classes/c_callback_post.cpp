#include "c_callback.hpp"

void                        c_callback::_check_is_body_to_large(void) {
    struct stat     stat;
    std::cout << "check body length" << std::endl;
    if (lstat(_tmpfile->get_filename().c_str(), &stat) != -1) {
        this->content_length_h = stat.st_size;
            if ((int)this->content_length_h >= client_max_body_size)
                this->status_code = 413;
    }
}

void                        c_callback::_create_tmp_file(void) {
    _tmpfile = new c_tmpfile();
    char            *line;
    char            *tmp;
    int             status;

    std::cout << "CREATE TMP FILE" << std::endl;
    if (this->client_max_body_size == -1)
        return ;
    if (*this->is_read_ready == false)
        --_it_recipes;
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

    tasks.push_back(&c_callback::_create_tmp_file);
    tasks.push_back(&c_callback::_check_is_body_to_large);
    tasks.push_back(&c_callback::_gen_resp_headers);
    tasks.push_back(&c_callback::_fd_is_ready_to_send);
    tasks.push_back(&c_callback::_send_respons);
    tasks.push_back(&c_callback::_send_respons_body);
    return tasks;
}
