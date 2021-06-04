#include "lib.hpp"
#include "utils.hpp"
#include "c_tmpfile.hpp"

/* CGITOHTTP
 * This function will read from the tmpfile where CGI output process is save
 * and store HTTP content that will be send to the client.
 *
 * RETURN:
 *  If syscall error occured, this function throw and error.
 *  If the first line of output isn't a Status header, this function return
 *    NULL.
 *  Else this function will parse the Status header and generate a Status-Line
 *    if the value of this header is a 3-digit know HTTP code.
 */

#define KEY_STATUS "Status: "

static std::string get_status(int fd, size_t *status_code) {
    char        *line = NULL;
    std::string status_line = "";

    if (get_next(fd, &line, "\r\n") == -1) {
        throw std::logic_error("cgitohttp(): [1] : get_next failed");
    } else if (line &&
            ft_strncmp(line, KEY_STATUS, ft_strlen(KEY_STATUS)) == 0) {
        *status_code = (size_t)ft_atoi(line + ft_strlen(KEY_STATUS));
        if (get_status_msg(*status_code) != "") {
            status_line = get_status_line(*status_code);
            status_line += "\r\n";
        }
    }
    if (line)
        free(line);
    return (status_line);
}


/* GET_HEADERS_LEN()
 * This function will read and return the len of all headers from CGI to
 * compute the content-lenth header value.
 */
static int         get_headers_len(int fd) {
    char    *headers = NULL;
    size_t  headers_len = 0;
    int     status;

    if ((status = get_next(fd, &headers, "\r\n\r\n")) == -1) {
        throw std::logic_error("cgitohttp(): [1] : get_next failed");
    } else if (headers) {
        headers_len += ((status ?: 1) - 1) + ft_strlen("\r\n\r\n");
        free(headers);
    }
    return (headers_len);
}

/* GET_CONTENT_LEN()
 * This function will return the entire HTTP header to send it to the client
 */
static std::string get_content_len(size_t tmpfile_size, int fd) {
    char        *str_content_len = NULL;
    std::string http_content = "";

    str_content_len = ft_itoa(tmpfile_size - (get_headers_len(fd)));
    http_content = "Content-Length: ";
    http_content += str_content_len;
    http_content += "\r\n";
    free(str_content_len);
    return (http_content);
}

char    *cgitohttp(c_tmpfile *tmpfile, size_t *status_code) {
    std::string http_content = "";

    http_content += get_status(tmpfile->get_fd(), status_code);
    if (*status_code / 100 != 2)
        return (NULL);
    if (http_content == "") {
        http_content += "HTTP/1.1 200 OK\r\n";
    }
    tmpfile->reset_cursor();
    get_next(tmpfile->get_fd(), NULL, "\r\n\r\n", GNL_FLUSH); // Flush GNL buffer
    http_content += get_content_len(tmpfile->get_size(), tmpfile->get_fd());
    tmpfile->reset_cursor();
    get_next(tmpfile->get_fd(), NULL, "\r\n\r\n", GNL_FLUSH); // Flush GNL buffer
    return (ft_strdup(http_content.c_str()));
}
