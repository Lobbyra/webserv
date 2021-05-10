#include "parse_request.hpp"

static void         init_request(s_request_header *request) {
    request->content_length = 0;
    request->error = 0;
}

s_request_header    read_request_header(int fd) {
    int                                         i = 0;
    int                                         status;
    char                                        *line;
    std::string                                 buf;
    s_request_header                            request;
    std::map<std::string, void *>               request_header;
    std::map<std::string, f_request_header>     parser_request;

    init_request(&request);
    request_header = init_request_header(&request);
    parser_request = init_parser_request();
    while ((status = get_next_line(fd, &line)) == 1) {
        buf = (std::string)line;
        if (buf.empty() == false && *(--buf.end()) == '\r') // Remove trailing
            buf.erase(--buf.end());
        if (buf.empty() == true && i < 1) {     // Flush \n before status line
            free(line);
            continue ;
        } else if (i == 0) {                            // Request line parsing
            if (buf[0] != ' ')
                parse_method(buf, request_header);
            i++;
        } else if (buf.empty() == false && i > -1) {     // Request header found
            parse_request_header(buf, request_header, parser_request);
        } else if (buf.empty() == true && i > 0) {      // Request message body
            free(line);
            break ;
        }
        free(line);
    }
    if (status == -1 && errno != EAGAIN) {
        throw std::logic_error(std::string("GNL: ") + strerror(errno));
    } else if (status == 0) {
        free(line);
    }
    return (request);
}
