#include "mini_serv.hpp"

static void        announce_client(int client_fd) {
    struct sockaddr_in  client_addr;
    int                 addr_len = sizeof(client_addr);

    if ((getsockname(client_fd,
                    (struct sockaddr *) &client_addr,
                    (socklen_t *) &addr_len))
        == -1) {
        std::cerr << "error: getsockname call" << std::endl;
        exit(1);
    }

    std::cout << COLOR_BLUE;
    std::cout <<                                           \
    "New request from " << inet_ntoa(client_addr.sin_addr) \
    << COLOR_RESET << std::endl;
}

static void        print_request(std::list<char *> request)
{
    std::cout << COLOR_GREEN;
    for (std::list<char *>::iterator it = request.begin();
         it != request.end();
         it++)
        std::cout << *it << std::endl;
    std::cout << COLOR_RESET;
}

static std::list<char *> request_reader(int client_fd) {
    char                        *buf;
    std::list<char *>           request;
    int                         status = 0;

    while ((status =
            get_next_line(client_fd, &buf)) > 0 && ft_strlen(buf) != 1) {
        request.push_back(buf);
    }
    if (status == -1) {
        std::cerr << "error: recv headers call : " << strerror(errno) \
            << std::endl;
        exit(1);
    }

    // get content-length
    std::list<char *>::iterator it = request.begin();
    char    content_key[] = "Content-length: ";
    while (it != request.end()
            && ft_strncmp(*it, content_key, 16) != 0) {
        it++;
    }
    if (it == request.end())  // return when no content-length is specified
        return (request);
    int content_len = ft_atoi(*it + 16);

    // body reading
    char    buf_2[content_len];
    if ((recv(client_fd, &buf_2, content_len, 0)) == -1) {
        std::cerr << "error: recv call : " << strerror(errno) \
            << std::endl;
        exit(1);
    }
    request.push_back(buf_2);
    return (request);
}

int listen_fd;

void        signal_handler(int signum) {
    std::cout << "(" << signum << ") Serveur ending..." << std::endl;
    close(listen_fd);
    exit(1);
}

void        mini_serv(int port) {
    /*
     * INIT
     */
    int client_fd;
    struct sockaddr_in listen_addr;

    // ctrl+c handling to close nicely the socket
    signal(SIGINT, signal_handler);

    // server socket creation
    if ((listen_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "error: socket creation" << std::endl;
        exit(1);
    }

    // init addr to listen to any address source of request
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    listen_addr.sin_port = htons(port);

    // link address to socket
    if ((bind(listen_fd, (struct sockaddr *) &listen_addr, sizeof(listen_addr)))
            == -1) {
        std::cerr << "error: socket creation" << std::endl;
        exit(1);
    }

    // turn socket in listen mode
    if ((listen(listen_fd, 5)) == -1) {
        std::cerr << "error: listen call" << std::endl;
        exit(1);
    }

    /*
     * SERVER WAITING LOOP
     */
    std::list<char *> request;
    while (1) {
        // Wait for a new request
        if ((client_fd = accept(listen_fd, NULL, NULL)) == -1) {
            std::cerr << "error: accept call" << std::endl;
            exit(1);
        }
        announce_client(client_fd);

        /*
         * READ THE REQUEST.
         */
        request = request_reader(client_fd);
        print_request(request);
        request.clear();

        /*
         *  SEND RESPONSE RESPONSE
         */
        std::string response;
        response += "HTTP/1.1 200 OK\n";
        response += "Content-Length: 13\n\n";
        response += "Hello World !\r\n\r\n";

        if ((send(client_fd, response.c_str(), response.length(), 0)) == -1) {
            std::cerr << "error: send call : " << strerror(errno) \
            << std::endl;
            return;
        }
        close(client_fd);
    }
}
