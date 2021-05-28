#include "c_callback.hpp"

extern bool g_verbose;

/* REMOVE_CLIENT
 * This function will remove the client from the list of clients next to failed
 * read. Bytes_read is the return of the read/recv on client_fd.
 */
void remove_client(std::list<s_socket> *clients, int client_fd,
                   ssize_t bytes_read) {
    std::string                   closing_cause = "";
    std::list<char*>::iterator    it_buf;
    std::list<char*>::iterator    ite_buf;
    std::list<s_socket>::iterator it = clients->begin();
    std::list<s_socket>::iterator ite = clients->end();

    for (; it != ite; ++it)
        if ((*it).client_fd == client_fd)
            break;
    if (g_verbose == true) {
        if (bytes_read == -1)
            closing_cause = "read error.";
        else if (bytes_read == 0)
            closing_cause = "client closed the connection.";
        std::cout <<                                          \
            "[" << it->client_fd << "] " <<               \
            "Connection closed due to : " << closing_cause << \
        std::endl;
    }
    it_buf = (*it).buffer.begin();
    ite_buf = (*it).buffer.end();
    while (it_buf != ite_buf) {
        free(*it_buf);
        (*it).buffer.erase(it_buf++);
    }
    close((*it).client_fd);
    clients->erase(it);
    return ;
}
