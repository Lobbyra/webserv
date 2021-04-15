#include "parse_request.hpp"

std::ostream& operator<<(std::ostream& os, s_request_header const &src)
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
    << "User-Agent: " << src.user_agent << std::endl            \
    << "Date: " << src.date << std::endl                        \
    << "Host: " << src.host << std::endl                        \
    << "Referer: " << src.referer << std::endl                  \
    << "Transfer-Encoding: " << src.transfer_encoding << std::endl \
    << "Content-Length: " << src.content_length << std::endl;

    return os;
};

s_request_header    read_request_header(void)
{
    int                                         i = 0;
    int                                         status;
    char                                        *line;
    std::string                                 buf;
    s_request_header                            request;
    std::map<std::string, void *>               request_header;
    std::map<std::string, f_request_header>     parser_request;

    request_header = init_request_header(&request);
    parser_request = init_parser_request();
    while ((status = get_next_line(0, &line)) == 1) {
        buf = (std::string)line;
        if (!line[0] && i < 1)
        {
            free(line);
            continue ;
        } else if (i == 0)                        // Request line
        {
            if (line[0] != ' ')
                parse_method(line, request_header);
            i++;
        } else if (line[0] && i > 0)           // Request header
        {
            parse_request_header(line, request_header, parser_request);
        } else if (!line[0] && i > 0)          // Request message body
        {
            free(line);
            break ;
        }
        free(line);
    }
    if (status == 0)
        free(line);
    std::cout << std::endl << request << std::endl;
    return (request);
}

// Function for multiple FD
// std::list<s_request_header>     parse_request(void)
// {
//     std::list<s_request_header>     list_requests;

//     while (list_fd)
//     {
//         list_requests.push_back(read_request_header());
//         list_fd = list_fd->nextl
//     }
//     return (list_requests);
// }

// int         main(void)
// {
//     read_request_header();
//     return (0);
// }
