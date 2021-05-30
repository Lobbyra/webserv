#include "lib.hpp"
#include <sys/socket.h>

#include "utils.hpp"
#include "c_callback.hpp"
#include "read_headers.hpp"

extern bool g_verbose;

#define CHUNK_CLOSE -3
#define CHUNK_FATAL -2
#define CHUNK_ERROR -1
#define CHUNK_MORE   0
#define CHUNK_ENOUGH 1
#define CHUNK_END    2

/* IS_STR_HEX
 * Return false is string in parameter does not contain only hex chars. Return
 * true else.
 */
static bool is_str_hex(char const *str) {
    while (*str) {
        if ((*str >= 'a' && *str <= 'f') || (*str >= 'A' && *str <= 'F') ||
                (*str >= '0' && *str <= '9')) {
            ++str;
        }
        else
            return (false);
    }
    return (true);
}

/* PARSE_CHUNK_DATA
 * This function will cut from the buffer all data until a CRLF and but it
 * in the tmpfile.
 */
int parse_chunk_data(std::list<char*> *buffer, int *chunk_size,
                            int tmpfile_fd) {
    int          ret_flag = CHUNK_MORE;
    int          chunk_data_len;
    char         *chunk_data = NULL;
    ssize_t      bytes_write;
    unsigned int len_to_cut;

    len_to_cut = find_str_buffer(buffer, "\r\n");
    chunk_data = cut_buffer_ret(buffer, len_to_cut);
    cut_buffer(buffer, 2);
    chunk_data_len = ft_strlen(chunk_data);
    if (chunk_data_len != *chunk_size) {
        std::cerr << "ERR : bad data chunk" << std::endl;
        ret_flag = CHUNK_ERROR;
    } else {
        bytes_write = write(tmpfile_fd, chunk_data, chunk_data_len);
        if (bytes_write == 0 || bytes_write == -1)
            ret_flag = CHUNK_FATAL;
    }
    *chunk_size = -1;
    free(chunk_data);
    return (ret_flag);
}

/* PARSE_CHUNK_SIZE
 * Will parse the buffer to find a chunk size.
 * If there isn't CRLF, it do nothing.
 */
int parse_chunk_size(std::list<char*> *buffer, int *chunk_size) {
    int          ret_flag = CHUNK_MORE;
    char         *size_line = NULL;
    unsigned int len_to_cut;

    len_to_cut = find_str_buffer(buffer, "\r\n");
    size_line = cut_buffer_ret(buffer, len_to_cut);
    cut_buffer(buffer, 2);
    if (is_str_hex(size_line) == false) {              // Size line non hex
        std::cerr << "ERR: parse_chunk_size: size not hex" << std::endl;
        ret_flag = CHUNK_ERROR;
    } else {
        *chunk_size = (int)hextodec(size_line);
    }
    if (ret_flag != CHUNK_ERROR && *chunk_size == 0) {
        ret_flag = CHUNK_END;
    }
    free(size_line);
    return (ret_flag);
}

#define CHUNK_BUF_SIZE 4096
#include <iostream>

/* READ_CHUNK_CLIENT
 * This function will read client and put the content in the buffer gived.
 */
int read_chunk_client(int client_fd, std::list<char*> *buffer) {
    int     ret_flag = CHUNK_MORE;
    char    *local_buf = NULL;
    ssize_t bytes_recv;

    if (!(local_buf = (char*)malloc(sizeof(char) * (CHUNK_BUF_SIZE))))
        return (CHUNK_FATAL);
    ft_bzero(local_buf, CHUNK_BUF_SIZE);
    errno = 0;
    bytes_recv = recv(client_fd, local_buf, CHUNK_BUF_SIZE - 1, 0);
    if (bytes_recv == 0 || bytes_recv == -1) {
        std::cerr << \
            "ERR: read_chunk_client : recv : " << bytes_recv << " " << \
            strerror(errno) << std::endl;
        ret_flag = CHUNK_CLOSE;
        free(local_buf);
    } else {
        buffer->push_back(local_buf);
        ret_flag = CHUNK_MORE;
    }
    return (ret_flag);
}

/* CHUNK_READING
 * This function will parse the client buffer and read the client if there is
 * no content to parse.
 */
void    c_callback::_chunk_reading(void) {
    if (g_verbose == true)
        std::cout << "TASK : _chunk_reading()" << std::endl;
    int status = CHUNK_MORE;

    if (_tmpfile == NULL)
        _tmpfile = new c_tmpfile();
    if (((is_buffer_crlf(this->client_buffer) == false &&
                *(this->is_read_ready) == false)) ||
                _tmpfile->is_write_ready() == false) {
        --_it_recipes;
        return ;
    }
    if (this->client_buffer->size() == 0 ||
            is_buffer_crlf(this->client_buffer) == false) {
        status = read_chunk_client(this->client_fd, this->client_buffer);
        if (status == CHUNK_CLOSE) {
            remove_client(this->clients, this->client_fd, 0);
            _exit();
            return ;
        }
    }
    while (is_buffer_crlf(this->client_buffer) && status != CHUNK_END) {
        if (this->_chunk_size == -1) {    // Chunk size is to read
            status = parse_chunk_size(this->client_buffer, &_chunk_size);
            if (this->client_max_body_size != -1 &&
                (int)_tmpfile->get_size() + _chunk_size >
                    this->client_max_body_size) {
                this->status_code = 413;
                return ;
            }
        } else {                           // We are reading the chunk data
            status = parse_chunk_data(this->client_buffer,
                                      &_chunk_size, _tmpfile->get_fd());
        }
    }
    if (status == CHUNK_MORE) {
        --_it_recipes;
    } else if (status == CHUNK_FATAL) {
        this->status_code = 500;
    } else if (status == CHUNK_ERROR) {
        this->status_code = 400;
    } else if (status == CHUNK_END) {
        _tmpfile->reset_cursor();
    }
    return ;
}
