# include "c_task_queue.hpp"

c_task_queue::c_task_queue(void) {
    return ;
}

c_task_queue::c_task_queue(c_task_queue const &src) {
    *this = src;
}

c_task_queue::~c_task_queue() {
    return ;
}

// Flush data in a fd
static void flush_fd(int fd) {
    get_next_line(fd, NULL);
}

// This function will remove finished request from client list
static void    remove_clients(std::list<s_socket> *clients, int client_fd) {
    std::list<s_socket>::iterator it  = clients->begin();
    std::list<s_socket>::iterator ite = clients->end();

    while (it != ite) {
        if (it->client_fd == client_fd) {
            flush_fd(client_fd);
            close(client_fd);
            clients->erase(it);
            break ;
        }
        ++it;
    }
}

// Will execute the last task in the queue and remove it if the recipe is done
void    c_task_queue::exec_task(void) {
    c_callback *front;

    if (_tasks.size() == 0)
        return;
    front = _tasks.front();
    front->exec();

    if (front->is_over() == true) {
        remove_clients(_clients, front->client_fd);
        _tasks.pop();
        delete front;
        return ;
    }
    _tasks.push(front);
    _tasks.pop();
}

// Add a new request in c_callback form in the queue
void    c_task_queue::push(std::list<s_request_header> &requests,
                           std::list<s_socket> *clients) {
    c_callback *cb_temp;
    std::list<s_socket>::iterator it_clients = clients->begin();
    std::list<s_socket>::iterator ite_clients = clients->end();
    std::list<s_request_header>::iterator it_requests = requests.begin();
    std::list<s_request_header>::iterator ite_requests = requests.end();

    while (it_clients != ite_clients && it_requests != ite_requests) {
        if (it_clients->server == NULL || it_clients->is_header_read) {
            ++it_clients;
            continue ;
        }
        cb_temp = new c_callback(*it_clients, *it_requests, clients);
        it_clients->is_header_read = true;
        _tasks.push(cb_temp);
        ++it_clients;
        ++it_requests;
    }
}

// Add client list to the queue
void    c_task_queue::set_clients(std::list<s_socket> *clients) {
    _clients = clients;
}

/*
 **    /// OPERATOR OVERLOADS PART \\
 */
c_task_queue    &c_task_queue::operator=(c_task_queue const &src) {
    (void)src;
    return (*this);
}
