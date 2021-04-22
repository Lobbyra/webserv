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

std::list<s_request_header>     parse_request(t_socketlst *const clients) {
    std::list<s_request_header>     list_requests;
    t_socketlst::iterator           it, ite;

    it = clients->begin();
    ite = clients->end();
    for (; it != ite; ++it) {
        if (it->is_read_ready == false || it->is_header_read || !it->client_fd)
            continue;
        list_requests.push_back(read_request_header(it->client_fd));
        it->is_header_read = true;
    }
    return (list_requests);
}

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