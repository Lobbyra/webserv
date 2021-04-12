#include "get_request_header.hpp"

c_request_header    read_request_header(void)
{
    int                                         i;
    int                                         status;
    char                                        *line;
    std::string                                 buf;
    c_request_header                            request;
    std::map<std::string, void *>               request_header;
    std::map<std::string, f_request_header>     parser_request;

    request_header = init_request_header(&request);
    parser_request = init_parser_request();
    i = 0;
    while ((status = get_next_line(0, &line)) == 1) {
        buf = (std::string)line;
        if (i == 0)     // Request line
            parse_method(line, request_header);
        // else            // Request header
        //     parse_request_header(line, request_header);
        free(line);
        i++;
    }
    if (status == 0)
        free(line);
    return (request);
}

int         main(void)
{
    read_request_header();
    return (0);
}