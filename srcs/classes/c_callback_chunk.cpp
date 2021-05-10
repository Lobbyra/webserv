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
    get_next_line(this->client_fd, &line);
    if (line[ft_strlen(line) - 1] == '\r')
        line[ft_strlen(line) - 1] = '\0';
    std::cout << "line = [" << line << "]" << std::endl << std::flush;
    if (is_str_hex(line) == false) { // Bad chunk size
        status_code = 400;
        free(line);
        return ;
    }
    _chunk_size = ft_atoi(line);
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
    bytes_read = 0;
    buf = NULL;
    while (get_next_line(this->client_fd, &buf) == 1 && // Read the chunk
            bytes_read < _chunk_size) {
        tmp_len = ft_strlen(buf);
        if (buf[tmp_len - 1] == '\r') {
            bytes_read += tmp_len - 1;
            buf[tmp_len - 1] = '\0';
            std::cout << "chunk = [" << buf << "]" << std::endl;
            write(_tmpfile->get_fd(), buf, tmp_len - 1);
            free(buf);
            break ;
        } else {
            bytes_read += tmp_len;
            std::cout << "chunk = [" << buf << "]" << std::endl;
            write(_tmpfile->get_fd(), buf, tmp_len);
            free(buf);
        }
    }
    if (bytes_read != _chunk_size) { // Chunk real size != _chunk_size
        std::cout << "bytes_read = " << bytes_read << std::endl;
        std::cout << "chunk_size = " << _chunk_size << std::endl;
        status_code = 400;
    } else {                                // Chunk well read n ok to save it
        --_it_recipes;
        --_it_recipes;
    }
}
