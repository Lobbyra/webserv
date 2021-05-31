#include "c_callback.hpp"

extern bool g_verbose;

/* REMOVE_CLIENT
 * This function will remove the given client from the list of client cause of
 * EOF/connection closed or recv return an error.
 * Bytes_read is the return of the read/recv on client_fd.
 */
void remove_client(std::list<s_socket> *clients, int client_fd,
                   ssize_t bytes_read) {
    std::string                   closing_cause;
    std::list<char*>::iterator    it_buf;
    std::list<char*>::iterator    ite_buf;
    std::list<s_socket>::iterator client = clients->begin();
    std::list<s_socket>::iterator client_ite = clients->end();

    for (; client != client_ite; ++client)
        if (client->client_fd == client_fd)
            break;
    if (g_verbose == true) {
        if (bytes_read == -1)
            closing_cause = "read error.";
        else if (bytes_read == 0)
            closing_cause = "client closed the connection.";
        std::cout <<                                          \
            "[" << client->client_fd << "] " <<               \
            "Connection closed due to : " << closing_cause << \
        std::endl;
    }
    it_buf = client->buffer.begin();
    ite_buf = client->buffer.end();
    while (it_buf != ite_buf) {
        free(*it_buf);
        client->buffer.erase(it_buf++);
    }
    close(client->client_fd);
    clients->erase(client);
    return ;
}
