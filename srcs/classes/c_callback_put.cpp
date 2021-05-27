#include "c_callback.hpp"
extern bool g_verbose;

#define PUT_OPEN_FLAGS (O_WRONLY | O_TRUNC)
#define PUT_OPEN_CREAT_FLAGS (O_WRONLY | O_TRUNC | O_CREAT)

void        c_callback::_meth_put_open_fd(void) {
    if (g_verbose)
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
        if (g_verbose)
            std::cerr << \
            "open() [" << path.c_str() << "] : " << strerror(errno) << \
            std::endl;
        this->status_code = 500;
        return ;
    }
}

/* _METH_PUT_CHOOSE_IN
 * This function will set which file descriptor in to take as input to write
 * data in the targeted file. Input file can be chunked request in a tmpfile
 * or a directly the client_fd body.
 */
void    c_callback::_meth_put_choose_in(void) {
    if (g_verbose)
        std::cout << "TASK : _meth_put_choose_in()" << std::endl;

    if (this->transfer_encoding == "chunked") {
        _put_fd_in = _tmpfile->get_fd();
    } else {
        _put_fd_in = this->client_fd;
    }
}

/* _METH_PUT_WRITE_BODY()
 */
void    c_callback::_meth_put_write_body(void) {
    if (g_verbose)
        std::cout << "TASK : _meth_put_write_body()" << std::endl;
    int  bytes_read = 0;
    char *buf;
    buf = NULL;

    if (this->transfer_encoding == "chunked") {     // [IN]  Tmpfile ready?
        if (_tmpfile->is_read_ready() == false) {
            --_it_recipes;
            return ;
        }
    }
    if (is_fd_write_ready(_fd_to_write) == false) { // [OUT] Target ready?
        --_it_recipes;
        return ;
    }
    if (*this->is_read_ready == true) {
        if (this->client_buffer->empty() == false) {
            buf = concate_list_str(this->client_buffer);
            bytes_read = ft_strlen(buf);
        } else {
            if (!(buf = (char *)malloc(sizeof(char) * 4096)))
            return ;
            bytes_read = read(_put_fd_in, &buf, 4096);
        }
        if (this->client_max_body_size != -1 &&
            bytes_read > (int)this->client_max_body_size) {
            free(buf);
            this->status_code = 413;
            return ;
        }
        if (bytes_read > 0) {
            if (write(_fd_to_write, buf, bytes_read) == -1) {
                if (transfer_encoding == "chunked") {
                    delete _tmpfile;
                    _tmpfile = NULL;
                }
                std::cerr << "_meth_put_write_body : write() failed" << std::endl;
                this->status_code = 500;
                return ;
            }
            --_it_recipes;
        } else if (bytes_read == -1) {
            std::cerr << "_meth_put_write_body : read() failed" << std::endl;
            this->status_code = 500;
            --_it_recipes;
            return ;
        }
    }
    else if (*this->is_read_ready == false) {
        if (this->client_buffer->empty() == false) {
            buf = concate_list_str(this->client_buffer);
            bytes_read = ft_strlen(buf);
        }
        if (bytes_read > 0) {
            if (write(_fd_to_write, buf, bytes_read) == -1) {
                if (transfer_encoding == "chunked") {
                    delete _tmpfile;
                    _tmpfile = NULL;
                }
            }
        }
    }
    if (bytes_read == 0 && transfer_encoding == "chunked") { // [END] chunked
        delete _tmpfile;
        _tmpfile = NULL;
    }
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
    tasks.push_back(&c_callback::_send_respons);
    tasks.push_back(&c_callback::_send_respons_body);
    return (tasks);
}
