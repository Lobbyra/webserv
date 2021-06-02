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

#define CHUNK_BUF_SIZE 4096

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

/* IS_CRLF_PART_FIRST()
 * This function return true if the first string in the buffer contain at least
 * one char of CRLF.
 */
static bool is_crlf_part_first(std::list<char*> *buffer) {
    char        *i_buf_part;
    std::string crlf = "\r\n";
    std::string str_comp_tmp;
    std::list<char*>::iterator it = buffer->begin();
    std::list<char*>::iterator ite = buffer->end();
    std::list<char*>::iterator it_first = buffer->end();

    str_comp_tmp.reserve(crlf.length());
    while (it != ite && str_comp_tmp != crlf) {
        i_buf_part = *it;
        while (*i_buf_part && str_comp_tmp != crlf) {
            if (*i_buf_part == '\r' || *i_buf_part == '\n') {
                if (str_comp_tmp.size() == 0 && *i_buf_part == '\r')
                    it_first = it;
                str_comp_tmp += *i_buf_part;
            } else if (str_comp_tmp.size() != 0) {
                str_comp_tmp.clear();
                if (it != buffer->begin())
                    return (false);
            }
            ++i_buf_part;
        }
        ++it;
        if (str_comp_tmp.empty() == true)
            return (false);
    }
    return (str_comp_tmp == crlf && it_first == buffer->begin());
}

int parse_chunk_data(std::list<char*> *buffer, int *chunk_size,
                    c_tmpfile *tmpfile, std::list<ssize_t> *len_buf_parts) {
    int          ret_flag = CHUNK_ENOUGH;
    int          chunk_data_len;
    char         *chunk_data = NULL;
    ssize_t      bytes_write = 1;

    while (is_crlf_part_first(buffer) == false &&
            tmpfile->is_write_ready() == true && bytes_write > 0) {
        bytes_write = write(tmpfile->get_fd(), buffer->front(),
                            len_buf_parts->front());
        free(buffer->front());
        *chunk_size -= len_buf_parts->front();
        buffer->pop_front();
        len_buf_parts->pop_front();
    }
    if (is_crlf_part_first(buffer) == true && *chunk_size >= 0 &&
            tmpfile->is_write_ready() == true && bytes_write > 0) {
        chunk_data_len = find_str_buffer(buffer, "\r\n");
        if (chunk_data_len > 0) {
            chunk_data = cut_buffer_ret(buffer, chunk_data_len, len_buf_parts);
            bytes_write = write(tmpfile->get_fd(), chunk_data, chunk_data_len);
            free(chunk_data);
            *chunk_size -= chunk_data_len;
        }
        cut_buffer(buffer, 2, len_buf_parts);
    }
    if (bytes_write == -1 || bytes_write == 0) {
        std::cerr << \
            "ERR: chunk_data : write failed : " << *chunk_size << \
        std::endl;
        ret_flag = CHUNK_FATAL;
    }
    if (*chunk_size != 0) {
        std::cerr << \
            "ERR: chunk_data : wrong chunk_len : " << *chunk_size << \
        std::endl;
        ret_flag = CHUNK_ERROR;
    }
    *chunk_size = -1;
    return (ret_flag);
}

bool g_fb;

/* PARSE_CHUNK_SIZE
 * Will parse the buffer to find a chunk size.
 * If there isn't CRLF, it do nothing.
 */
int parse_chunk_size(std::list<char*> *buffer, int *chunk_size,
        std::list<ssize_t> *len_buf_parts) {
    int          ret_flag = CHUNK_ENOUGH;
    char         *size_line = NULL;
    unsigned int len_to_cut;

    if (**(buffer->begin()) == '0') {
        if (find_str_buffer(buffer, "\r\n\r\n") == 1 ||
                (g_fb && find_str_buffer(buffer, "\r\n\r")))
            return (CHUNK_END);
        else if (find_str_buffer(buffer, "\r\n") == 1)
            return (CHUNK_ENOUGH);
    }
    len_to_cut = find_str_buffer(buffer, "\r\n");
    size_line = cut_buffer_ret(buffer, len_to_cut, len_buf_parts);
    cut_buffer(buffer, 2, len_buf_parts);
    if (is_str_hex(size_line) == false) {              // Size line non hex
        std::cerr << "ERR: parse_chunk_size: size not hex" << std::endl;
        ret_flag = CHUNK_ERROR;
    } else {
        *chunk_size = (int)hextodec(size_line);
    }
    if (*chunk_size == 100)
        g_fb = true;
    else
        g_fb = false;
    free(size_line);
    return (ret_flag);
}

#include <iostream>

/* READ_CHUNK_CLIENT
 * This function will read client and put the content in the buffer gived.
 */
int read_chunk_client(int client_fd, std::list<char*> *buffer,
        std::list<ssize_t> *len_buf_parts) {
    int     ret_flag = CHUNK_ENOUGH;
    char    *local_buf = NULL;
    ssize_t bytes_recv;

    if (!(local_buf = (char*)malloc(sizeof(char) * (CHUNK_BUF_SIZE + 1))))
        return (CHUNK_FATAL);
    ft_bzero(local_buf, CHUNK_BUF_SIZE + 1);
    bytes_recv = recv(client_fd, local_buf, CHUNK_BUF_SIZE, 0);
    if (bytes_recv == 0 || bytes_recv == -1) {
        std::cerr << \
            "ERR: read_chunk_client : recv : " << bytes_recv << std::endl;
        ret_flag = CHUNK_CLOSE;
        free(local_buf);
    } else {
        buffer->push_back(local_buf);
        len_buf_parts->push_back(bytes_recv);
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
    int status = CHUNK_ENOUGH;

    if (_tmpfile == NULL)
        _tmpfile = new c_tmpfile();
    if (((is_buffer_crlf(this->client_buffer) == false &&
            *(this->is_read_ready) == false)) ||
            _tmpfile->is_write_ready() == false) {
        --_it_recipes;
        return ;
    }
    if (is_buffer_crlf(this->client_buffer) == false) {
        status = read_chunk_client(this->client_fd, this->client_buffer,
                                   &(this->client->len_buf_parts));
        if (status == CHUNK_CLOSE) {
            remove_client(this->clients, this->client_fd, 0);
            _exit();
            return ;
        } else if (status == CHUNK_FATAL) {
            this->status_code = 500;
            return ;
        }
    }
    if (is_buffer_crlf(this->client_buffer) == false) {
        --_it_recipes;
        return ;
    }
    if (_chunk_size == -1) {     // Parse chunk size
        status = parse_chunk_size(this->client_buffer, &_chunk_size,
                            &(this->client->len_buf_parts));
    } else {                           // Read chunk data
        status = parse_chunk_data(this->client_buffer, &_chunk_size, _tmpfile,
                            &(this->client->len_buf_parts));
    }
    if (this->client_max_body_size != -1 &&
            (int)_tmpfile->get_size() > this->client_max_body_size) {
        this->status_code = 413;
    } else if (status == CHUNK_FATAL) {
        this->status_code = 500;
    } else if (status == CHUNK_ERROR) {
        this->status_code = 400;
    } else if (status == CHUNK_END) {
        _tmpfile->reset_cursor();
    } else {
        --_it_recipes;
    }
    return ;
}
