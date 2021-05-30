#include <list>

#include <stdlib.h>

/* IS_BUFFER_CRLF
 * This function will return true if the buffer contain a CRLF.
 */
bool    is_buffer_crlf(std::list<char*> *buffer) {
    char  str_crlf[] = "\r\n";
    char  *i_buf_parts = NULL;
    short i_crlf = 0;
    std::list<char*>::iterator it_buf = buffer->begin();
    std::list<char*>::iterator ite_buf = buffer->end();

    while (it_buf != ite_buf && str_crlf[i_crlf] != '\0') {
        i_buf_parts = *it_buf;
        while (*i_buf_parts != '\0' && str_crlf[i_crlf] != '\0') {
            if (*i_buf_parts == str_crlf[i_crlf]) {
                ++i_crlf;
            } else if (i_crlf != 0) {
                i_crlf = 0;
            }
            ++i_buf_parts;
        }
        ++it_buf;
    }
    if (str_crlf[i_crlf] == '\0')
        return (true);
    return (false);
}

/*
#include <iostream>
int         main(int argc, char **argv) {
    std::list<char*> buffer;

    if (argc == 1) {
        return (1);
    } else {
        ++(*argv);
        while (*argv) {
            buffer.push_back(*argv);
            ++argv;
        }
        std::cout << std::boolalpha << is_buffer_crlf(&buffer) << std::endl;
    }
    return (0);
}
*/
