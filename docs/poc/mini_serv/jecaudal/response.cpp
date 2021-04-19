#include "mini_serv.hpp"

// Response from a string
static void     r_string(int client_fd) {
    std::string response;
    response += "HTTP/1.1 200 OK\n";
    response += "Content-Length: 13\n\n";
    response += "Hello World !\r\n\r\n";
    if ((send(client_fd, response.c_str(), response.length(), 0)) == -1) {
        std::cerr << "error: send call : " << strerror(errno) \
        << std::endl;
        return;
    }
}

// Response from a file
static void     r_file(int client_fd) {
    int fd = open("index.html", O_RDONLY);
    char buf[56];

    bzero(buf, 56);
    while (read(fd, buf, 56) > 0) {
        send(client_fd, buf, 56, 0);
        bzero(buf, 56);
    }
}

// Response from stdout of a child
void    r_child(int client_fd) {
    int pid;

    pid = 0;
    errno = 0;
    if ((pid = fork()) == 0) {
        char *path = "/bin/echo";
        char *argv[] = {"echo", "salut", NULL};

        dup2(client_fd, STDOUT);
        std::cerr << "Starting the child..." << std::endl;
        if (execve(path, argv, NULL) == -1)
            std::cerr << strerror(errno) << std::endl;
        exit(0);
    } else {
        std::cout << "Waiting for the child..." << std::endl;
        waitpid(pid, NULL, 0);
        std::cout << "Child died." << std::endl;
    }
}

void    response(int client_fd) {
    //r_file(client_fd);
    r_child(client_fd);
    //r_string(client_fd);
}
