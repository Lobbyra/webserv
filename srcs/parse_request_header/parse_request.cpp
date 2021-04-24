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
        s_request_header new_request_header;

        try {
            new_request_header = read_request_header(it->client_fd);
        }
        catch (const std::exception &e) {
            std::cerr << "Request header: " << e.what() << std::endl;
            clients->erase(it++);
            --it;
            continue ;
        }
        list_requests.push_back(new_request_header);
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
