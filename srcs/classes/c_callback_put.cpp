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
    if (lstat(this->path.c_str(), &stat) == 0 && // File exist and not a dir
            S_ISDIR(stat.st_mode) == false) {
        this->status_code = 204;
        flags = PUT_OPEN_FLAGS;
        mode = 0;
    } else if (S_ISDIR(stat.st_mode) == true) {  // Path is dir
        this->status_code = 409;
        return ;
    } else {                                     // File does not exist
        this->status_code = 201;
        flags = PUT_OPEN_CREAT_FLAGS;
        mode = S_IRWXU;
    }
    if ((_fd_to_write = open(path.c_str(), flags, mode)) == -1) {
        std::cerr <<                                              \
        "open() [" << path.c_str() <<"] : " << strerror(errno) << \
        std::endl;
        this->status_code = 500;
        return ;
    }
    _continue();
}

void    c_callback::_meth_put_choose_in(void) {
    std::cout << "TASK : _meth_put_choose_in()" << std::endl;

    if (this->transfer_encoding == "chunked") {
        _put_fd_in = _tmpfile->get_fd();
    } else {
        _put_fd_in = this->client_fd;
    }
    _continue();
}

#define PUT_BUFFER_SIZE 4096

/* _METH_PUT_WRITE_BODY()
 */
void    c_callback::_meth_put_write_body(void) {
    std::cout << "TASK : _meth_put_write_body()" << std::endl;
    int  line_len;
    int  bytes_read;
    char *buf;

    buf = NULL;
    if (this->transfer_encoding == "chunked") {     // Tmpfile ready?
        if (_tmpfile->is_read_ready() == false) {
            --_it_recipes;
            return ;
        }
    } else {                                        // Client ready?
        if (this->is_read_ready == false) {
            --_it_recipes;
            return ;
        }
    }
    if (is_fd_write_ready(_fd_to_write) == false) { // Target ressource ready?
        --_it_recipes;
        return ;
    }
    while ((bytes_read = get_next_line(_put_fd_in, &buf)) == 1) {
        std::cout << "buf = " << buf << std::endl;
        line_len = ft_strlen(buf);
        if (line_len > 0 && buf[line_len - 1] == '\r')
            buf[--line_len] = '\0';
        write(_fd_to_write, buf, line_len);
        write(_fd_to_write, "\n", 1);
        free(buf);
        buf = NULL;
    }
    if (bytes_read == 0 && buf != NULL) {
        write(_fd_to_write, buf, ft_strlen(buf));
        free(buf);
        buf = NULL;
    }
    std::cout << bytes_read << std::endl;
    if (transfer_encoding == "chunked")
        delete _tmpfile;
    _continue();
}

std::list<c_callback::t_task_f>         c_callback::_init_recipe_put(void){
    std::list<t_task_f> tasks;

    if (this->transfer_encoding == "chunked") {
        tasks.push_back(&c_callback::_chunk_reading_size);
        tasks.push_back(&c_callback::_chunk_reading_chunk);
    }
    tasks.push_back(&c_callback::_meth_put_open_fd);
    tasks.push_back(&c_callback::_meth_put_choose_in);
    tasks.push_back(&c_callback::_meth_put_write_body);
    tasks.push_back(&c_callback::_gen_resp_headers);
    tasks.push_back(&c_callback::_fd_is_ready_to_send);
    tasks.push_back(&c_callback::_send_respons);
    return (tasks);
}
