#include <list>
#include <string>

#include "read_headers.hpp"

/* GET_HEADER
 * This function return the header if a CRLF is in the buffer. Else return
 * empty string. If second parameter is to true, this function will flush CR
 * and LF chars before the first char and try to get the header.
 */
#define CRLF "\r\n"

#include <iostream>

std::string get_header(std::list<char*> *buf_header,
                       bool is_status_line_read) {
    char         *str_tmp = NULL;
    std::string  final_header = "";
    unsigned int header_len = 0;

    if (is_status_line_read == false)
        flush_crlf(buf_header);
    if (find_str_buffer(buf_header, CRLF) == 0)
        return ("");
    header_len = find_str_buffer(buf_header, CRLF);
    std::cout << header_len << std::endl;
    str_tmp = cut_buffer_ret(buf_header, header_len);
    cut_buffer(buf_header, 2);
    final_header = str_tmp;
    free(str_tmp);
    return (final_header);
}

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
    std::list<char*>    buf_header;

    fd = open("test.txt", O_RDONLY);
    buf = (char*)malloc(sizeof(char) * 2);
    ft_bzero(buf, 2);
    while (read(fd, buf, 1) != 0) {
        buf_header.push_back(buf);
        buf = (char*)malloc(sizeof(char) * 2);
        ft_bzero(buf, 2);
    }

    std::cout <<                                                           \
        "buf_header.size() before get_header() : " << buf_header.size() << \
    std::endl;
    std::cout <<                                                          \
        "buf_header before get_header() : " << std::endl << buf_header << \
    std::endl;

    while ((header = get_header(&buf_header, IS_STATUS_LINE_READ)) != "") {
        std::cout <<                                               \
            "get_header() = [" << header << "]" << \
        std::endl;
    }

    std::cout <<                                                          \
        "buf_header.size() after get_header() : " << buf_header.size() << \
    std::endl;
    std::cout <<                                                         \
        "buf_header after get_header() : " << std::endl << buf_header << \
    std::endl;
    for (std::list<char*>::iterator it = buf_header.begin();
            it != buf_header.end();
            ++it) {
        free(*it);
    }
    return (0);
}
