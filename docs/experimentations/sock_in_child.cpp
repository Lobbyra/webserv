/*
 * Experimentation of socket reading in child. This is about cgi request
 * redirection. It's a test to know if we can still read a socket in a child
 * process duped in stdin.
 * 
 * The goal is to avoid data buffering. We just want to read the header and let
 * the cgi continue to read data from client socket.
 */

#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>

#define LISTEN_PORT 18000

int listen_fd;

void        signal_handler(int signum) {
    std::cout << "(" << signum << ") Serveur ending..." << std::endl;
    close(listen_fd);
    exit(1);
}

void        init_socket(int *listen_fd) {
    struct sockaddr_in listen_addr;

    // server socket creation
    if ((*listen_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "error: socket creation" << std::endl;
        exit(1);
    }

    // init addr to listen to any address source of request
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    listen_addr.sin_port = htons(LISTEN_PORT);

    // link address to socket
    if ((bind(*listen_fd, (struct sockaddr *) &listen_addr, sizeof(listen_addr)))
            == -1) {
        std::cerr << "error: socket creation" << std::endl;
        exit(1);
    }

    // turn socket in listen mode
    if ((listen(*listen_fd, 5)) == -1) {
        std::cerr << "error: listen call" << std::endl;
        exit(1);
    }
}

int         main(void) {
    int client_fd;
    char buf[1];

    signal(SIGINT, signal_handler);

    errno = 0;
    init_socket(&listen_fd);
    if ((client_fd = accept(listen_fd, NULL, NULL)) == -1) {
        std::cerr << "error: accept call" << std::endl;
        exit(1);
    }
    while (recv(client_fd, buf, 1, 0) > 0) {
        write(1, &(buf[0]), 1);
        if (buf[0] == ';') {
            break;
        }
    }
    if (fork() == 0) {
        std::cout << "child process..." << std::endl;
        dup2(client_fd, 0);
        while (read(0, buf, 1) > 0) {
            write(1, &(buf[0]), 1);
            if (buf[0] == ';') {
                break;
            }
        }
        close(client_fd);
    } else {
        wait(NULL);
        close(client_fd);
        close(listen_fd);
        std::cout << "exit main procc" << std::endl;
    }
    return (0);
}
