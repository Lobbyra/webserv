#include <list>
#include <string>
#include <iostream>

#include <stdlib.h>

#include "read_headers.hpp"
#include "insert_stream_cont.hpp"

/* GET_HEADER
 * This function return the header if a CRLF is in the buffer. Else return
 * empty string. If second parameter is to true, this function will flush CR
 * and LF chars before the first char and try to get the header.
 */
#define CRLF "\r\n"

std::string get_header(std::list<char*> *buffer, bool is_status_line_read,
        std::list<ssize_t> *len_buf_parts) {
    char         *str_tmp = NULL;
    std::string  final_header = "";
    unsigned int header_len = 0;

    if (is_status_line_read == false)
        flush_crlf(buffer, len_buf_parts);
    if (find_str_buffer(buffer, CRLF) == 0)
        return ("");
    header_len = find_str_buffer(buffer, CRLF);
    str_tmp = cut_buffer_ret(buffer, header_len, len_buf_parts);
    cut_buffer(buffer, 2, len_buf_parts);
    final_header = str_tmp;
    free(str_tmp);
    return (final_header);
}

/*
#define IS_STATUS_LINE_READ false
#include <iostream>
#include "lib.hpp"
#include "utils.hpp"
#include "colors.hpp"
#include <fcntl.h>
int         main(void) {
    int  fd;
    char *buf = NULL;
    std::string         header = "";
    std::list<char*>    buffer;

    fd = open("test.txt", O_RDONLY);
    buf = (char*)malloc(sizeof(char) * 2);
    ft_bzero(buf, 2);
    while (read(fd, buf, 1) != 0) {
        buffer.push_back(buf);
        buf = (char*)malloc(sizeof(char) * 2);
        ft_bzero(buf, 2);
    }

    std::cout <<                                                           \
        "buffer.size() before get_header() : " << buffer.size() << \
    std::endl;
    std::cout <<                                                          \
        "buffer before get_header() : " << std::endl << buffer << \
    std::endl;

    while ((header = get_header(&buffer, IS_STATUS_LINE_READ)) != "") {
        std::cout <<                                               \
            "get_header() = [" << header << "]" << \
        std::endl;
    }

    std::cout <<                                                          \
        "buffer.size() after get_header() : " << buffer.size() << \
    std::endl;
    std::cout <<                                                         \
        "buffer after get_header() : " << std::endl << buffer << \
    std::endl;
    for (std::list<char*>::iterator it = buffer.begin();
            it != buffer.end();
            ++it) {
        free(*it);
    }
    return (0);
}
*/
