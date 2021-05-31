#include <list>
#include <string>

#include "read_headers.hpp"

/* FLUSH_CRLF
 * This function will remove starting '\r' & '\n' of the buffer.
 */
bool    flush_crlf(std::list<char*> *buffer,
        std::list<ssize_t> *len_buf_parts) {
    char         *i_buf_parts = NULL;
    unsigned int len_to_flush = 0;
    std::list<char*>::iterator    it = buffer->begin();
    std::list<char*>::iterator    ite = buffer->end();

    while (it != ite) {
        i_buf_parts = *it;
        while (*i_buf_parts == '\r' || *i_buf_parts == '\n') {
            ++i_buf_parts;
            ++len_to_flush;
        }
        if (*i_buf_parts != '\0')
            break;
        ++it;
    }
    cut_buffer(buffer, len_to_flush, len_buf_parts);
    return (len_to_flush > 0);
}

/*
#include "utils.hpp"
#include "lib.hpp"
int     main(int argc, char **argv) {
    char **i_argv = NULL;
    std::list<char*> buffer;

    if (argc == 1) {
        std::cerr << "Wrong arguments" << std::endl;
        return (1);
    }
    // BUFFER INIT
    i_argv = argv + 1;
    while (*i_argv) {
        buffer.push_back(ft_strdup(*i_argv));
        ++i_argv;
    }

    // TEST CALL
    std::cout << \
    "buffer before size : " << buffer.size() << std::endl;
    std::cout << "buffer after : " << std::endl << buffer << std::endl;
    std::cout << std::endl;
    flush_crlf(&buffer);
    std::cout << \
    "buffer after size : " << buffer.size() << std::endl;
    std::cout << "buffer after : " << std::endl << buffer << std::endl;

    // FREE REMAINING CHARS
    for (std::list<char*>::iterator it = buffer.begin(); it != buffer.end();
            ++it) {
        free(*it);
    }
    return (0);
}
*/
