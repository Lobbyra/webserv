# include "c_callback.hpp"

void remove_client(std::list<s_socket> *clients, int client_fd) {
    std::string closing_cause = "";
    std::list<s_socket>::iterator       it = clients->begin();
    std::list<s_socket>::iterator       ite = clients->end();
    std::list<char*>::iterator          it_buf;
    std::list<char*>::iterator          ite_buf;
    

    for (; it != ite; ++it)
        if ((*it).client_fd == client_fd)
            break;
    it_buf = (*it).buf_header.begin();
    ite_buf = (*it).buf_header.end();
    while (it_buf != ite_buf) {
        free(*it_buf);
        (*it).buf_header.erase(it_buf++);
    }
    close((*it).client_fd);
    clients->erase(it);
    return ;
}