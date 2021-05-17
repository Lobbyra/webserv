#include "parse_request.hpp"
extern bool g_verbose;

std::list<s_request_header>     parse_request(t_socketlst *const clients) {
    std::list<s_request_header>     list_requests;
    t_socketlst::iterator           it, ite;

    it = clients->begin(); 
    ite = clients->end();
    for (; it != ite; ++it) {
        if (it->is_read_ready == false || it->is_header_read || !it->client_fd)
            continue;
        s_request_header new_request_header;
        new_request_header = read_request_header(it->client_fd);
        if (new_request_header.error == 42) {
            close(it->client_fd);
            clients->erase(it--);
            continue ;
        }
        if (g_verbose)
            std::cout << new_request_header;
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
