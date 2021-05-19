#include "parse_request.hpp"

/* PARSE_REQ_LINE()
 * Function that will read one time and parse the request line.
 */
static void         parse_req_line(int client_fd,
                                 std::map<std::string,void *> req_headers) {
    int status;
    char *buf;

    usleep(1000);
    while ((status = get_next(client_fd, &buf, "\r\n")) == 1) {
        if (buf[0] != '\0')
            break ;
        usleep(5000);
    }

    status = get_next(client_fd, &buf, "\r\n");
    std::cout << "Status:" << status << "buf:" << buf << "." << "  errno: " << strerror(errno) << std::endl;
    if (status == 0) {
        throw std::exception();
        free(buf);
    }
    if (status != -1) {
        parse_method(buf, req_headers);
        free(buf);
    }
}

/* READ_REQUEST_HEADER()
 * This function will read the client until the empty line and will parse the
 * header to create the s_request_header structure.
 */
s_request_header    read_request_header(int client_fd) {
    int                                     status;
    int                                     line_len;
    char                                    *line;
    s_request_header                        request;
    std::map<std::string, void *>           request_header;
    std::map<std::string, f_request_header> parser_request;

    line = NULL;
    request.error = 200;
    request.content_length = 0;
    request_header = init_request_header(&request);
    parser_request = init_parser_request();
    try {
        parse_req_line(client_fd, request_header);
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        request.error = 42;
        return (request);
    }
    if (request.error >= 400 || request.method == "TRACE") {
        if (request.method == "TRACE")
            request.host = "tmp";
        return (request);
    }
    while ((status = get_next(client_fd, &line, "\r\n")) == 1) {
        line_len = ft_strlen(line);
        if (line_len == 0 || request.error >= 400)
            break;
        if (parse_request_header(line, request_header, parser_request) == 1)
            request.error = 400;
        request.saved_headers.push_back(line);
        free(line);
        line = NULL;
    }
    if (line != NULL)
        free(line);
    return (request);
}

// int         main(void) {
//     // std::cout << read_request_header(0) << std::endl;
//     int fd;
//     char *line = NULL;
//     int ret;
//     fd = open("test_gnl", O_RDONLY);
//     while ((ret = get_next(fd, &line, "\r\n")) > 0) {
//         std::cout << "RET: " << ret << " | LINE:" << line << std::endl;
//     }
//     std::cout << "RET: " << ret << " | LINE:" << line << std::endl;
//     return (0);
// }

