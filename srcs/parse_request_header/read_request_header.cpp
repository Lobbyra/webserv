#include "parse_request.hpp"

/* PARSE_REQ_LINE()
 * Function that will read one time and parse the request line.
 */
static void         parse_req_line(int client_fd,
                                 std::map<std::string,void *> req_headers) {
    int status;
    char *buf;

    status = get_next(client_fd, &buf, "\r\n");
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
    parse_req_line(client_fd, request_header);
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

/*
int         main(void) {
    std::cout << read_request_header(0) << std::endl;
    return (0);
}
*/
