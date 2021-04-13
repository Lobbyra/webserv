#include "webserv.hpp"
#include <sys/socket.h>
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h> // inet_pton
#include <fcntl.h>

typedef struct sockaddr t_sockaddr;
typedef struct sockaddr_in t_sockaddr_in;

static int  makeSocket(const int &port) {
    int newSocket;
    t_sockaddr_in servaddr;

    if ((newSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        ft_error("socket");

    fcntl(newSocket, F_SETFL, O_NONBLOCK);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if ((bind(newSocket, (t_sockaddr *)&servaddr, sizeof(servaddr))) < 0)
        ft_error("bind");
    if ((listen(newSocket, 10)) < 0)
        ft_error("listen");
	return (newSocket);
}

t_fdlst	init_listen(std::list<c_server> const &conf) {
    t_fdlst res;
	std::list<c_server>::const_iterator it = conf.begin(), ite = conf.end();

	for (; it != ite; ++it)
		res.push_back(makeSocket(it->listen.port));
    return (res);
}
