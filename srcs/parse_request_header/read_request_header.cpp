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

s_request_header    read_request_header(int fd) {
    int                                         i = 0;
    int                                         status;
    char                                        *line;
    std::string                                 buf;
    s_request_header                            request;
    std::map<std::string, void *>               request_header;
    std::map<std::string, f_request_header>     parser_request;

    request_header = init_request_header(&request);
    parser_request = init_parser_request();
    while ((status = get_next_line(fd, &line)) == 1) {
        buf = (std::string)line;
        if (buf.empty() == false && *(--buf.end()) == '\r')
            buf.erase(--buf.end());
        if (buf.empty() == true && i < 1) {
            free(line);
            continue ;
        } else if (i == 0) {                            // Request line
            if (buf[0] != ' ')
                parse_method(buf, request_header);
            i++;
        } else if (buf.empty() == false && i > 0) {     // Request header
            parse_request_header(buf, request_header, parser_request);
        } else if (buf.empty() == true && i > 0) {      // Request message body
            free(line);
            break ;
        }
        free(line);
    }
    if (status == 0)
        free(line);
    return (request);
}

std::list<s_request_header>     parse_request(t_socketlst clients) {
    std::list<s_request_header>     list_requests;
    t_socketlst::iterator           it, ite;

    it = clients.begin();
    ite = clients.end();
    for (; it != ite; ++it)
        list_requests.push_back(read_request_header((*it).client_fd));
    return (list_requests);
}

// volatile bool g_run = 1;

// int         main(int ac, char **av)
// {
//     int                 fd;
//     s_request_header    request;

//     fd = open(av[ac - 1], O_RDONLY);
//     std::cout << "FD :" << fd << std::endl << std::endl;
//     request = read_request_header(fd);
//     std::cout << request << std::endl;
//     return (0);
// }
