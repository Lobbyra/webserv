#include "c_callback.hpp"

/* IS_STR_HEX
 * Return false is string in parameter does not contain only hex chars. Return
 * true else.
 */
static bool is_str_hex(char const *str) {
    while (*str) {
        if ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z') ||
                (*str >= '0' && *str <= '9')) {
            ++str;
        }
        else
            return (false);
    }
    return (true);
}

/* CHUNK_READING_SIZE
 * This function will read the chunk size from client_fd.
 * It will check if the size is hexadecimal and if it contain only hexa chars.
 */
void    c_callback::_chunk_reading_size(void) {
    std::cout << "TASK : _CHUNK_READING_SIZE" << std::endl;
    char *line;

    _chunk_size = 0;
    if (this->_tmpfile == NULL)
        this->_tmpfile = new c_tmpfile();
    if (this->is_read_ready == false) {
        _it_recipes--;
        return ;
    }
    if (get_next(this->client_fd, &line, "\r\n") == -1) { // Ending chunk miss
        this->status_code = 400;
        return ;
    }
    if (is_str_hex(line) == false) { // Non hexad chunk size
        status_code = 400;
        free(line);
        return ;
    }
    _chunk_size = hextodec(line);
    if (_chunk_size == 0) {
        _tmpfile->reset_cursor();
        ++_it_recipes;
    }
    free(line);
}

/* CHUNK_READING_CHUNK
 * This function will read the chunk from client_fd.
 */
void    c_callback::_chunk_reading_chunk(void) {
    std::cout << "TASK : _CHUNK_READING_CHUNK" << std::endl;
    int  tmp_len;
    int  bytes_read;
    char *buf;

    if (this->is_read_ready == false || _tmpfile->is_write_ready() == false) {
        --_it_recipes;                      // Wait until all fd are ready
        return ;
    }
    tmp_len = 0;
    buf = NULL;
    get_next(this->client_fd, &buf, "\r\n");
    bytes_read = ft_strlen(buf);
    if (bytes_read != _chunk_size) {
        std::cerr << \
        "ERROR : chunk_len != chunk gived" << bytes_read << std::endl;
        status_code = 400;
        return ;
    }
    write(_tmpfile->get_fd(), buf, bytes_read);
    --_it_recipes;
    --_it_recipes; // Go to chunk read size
}