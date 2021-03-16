#include "mini_client.hpp"

void    mini_client(net_dest server)
{
    int sockfd;
    struct sockaddr_in s_addr;

    errno = 0;
    /*
     *  INIT
     */
    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "error: socket creation : " << strerror(errno) \
        << std::endl;
        return;
    }
    bzero(&s_addr, sizeof(sockaddr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(server.port);
    s_addr.sin_addr.s_addr = server.ip;

    /*
     *  CONNECT
     */
    if ((connect(sockfd, (struct sockaddr*) &s_addr, sizeof(s_addr))) == -1) {
        std::cerr << "error: connect call : " << strerror(errno) \
        << std::endl;
        return;
    }

    /*
     *  CREATE REQUEST
     */
    char request[] = "GET / HTTP/1.1\nHost: example.com\r\n\r\n";

    /*
     *  SEND
     */
    if ((send(sockfd, request, ft_strlen(request), 0)) == -1) {
        std::cerr << "error: send call : " << strerror(errno) \
        << std::endl;
        return;
    }

    /*
     *  READ RESPONSE
     */
    // GET HEADERS + STATUS LINE
    char                        *buf;
    std::vector<std::string>    response;
    int                         status = 0;
    while ((status = get_next_line(sockfd, &buf)) > 0 && ft_strlen(buf) != 1) {
        response.push_back(buf);
    }
    if (status == -1) {
        std::cerr << "error: recv headers call : " << strerror(errno) \
        << std::endl;
        return;
    }

    // get content-length
    std::vector<std::string>::iterator  it = response.begin();
    while (ft_strncmp((*it).c_str(), "Content-Length: ", 16) != 0
        && it != response.end()) {
        it++;
    }
    std::string content_len_head = *it;
    content_len_head.erase(0, 16);
    int content_len = ft_atoi(content_len_head.c_str());

    // body reading
    char    buf_2[content_len];
    if ((recv(sockfd, &buf_2, content_len, 0)) == -1) {
        std::cerr << "error: recv call : " << strerror(errno) \
        << std::endl;
        return;
    }
    response.push_back(buf_2);
    for (std::vector<std::string>::iterator it = response.begin();
        it != response.end();
        it++)
        std::cout << *it << std::endl;
    return;
}
