#include "parse_request.hpp"

std::ostream& operator<<(std::ostream& os, c_request_header const &src)
{
    os << "Request line: " << std::endl                 \
    << "Method: " << src.method << "." << std::endl     \
    << "Path: " << src.path << "." << std::endl         \
    << "Protocol: " << src.protocol << "." << std::endl \
    << "Error: " << src.error << "." << std::endl << std::endl  \
    << "Request header: " << std::endl                          \
    << "Accept-charset: " << src.accept_charset << std::endl    \
    << "Accept-language: " << src.accept_language << std::endl  \
    << "Authorization: " << src.authorization << std::endl      \
    << "Content-Type: " << src.content_type << std::endl        \
    << "User-Agent: " << src.user_agent << std::endl;

    return os;
};

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
        if (!line[0] && i < 1)
            continue ;
        else if (i == 0)     // Request line
        {
            if (line[0] != ' ')
                parse_method(line, request_header);
            i++;
        }
        else if (i > 0)           // Request header
        {
            parse_request_header(line, request_header, parser_request);
        }
        free(line);
    }
    if (status == 0)
        free(line);
    std::cout << std::endl << request << std::endl;
    return (request);
}

int         main(void)
{
    read_request_header();
    return (0);
}
