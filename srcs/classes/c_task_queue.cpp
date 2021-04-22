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

// This function will remove finished request from client list
static void    remove_clients(std::list<s_socket> *clients, int client_fd) {
    std::list<s_socket>::iterator it  = clients->begin();
    std::list<s_socket>::iterator ite = clients->end();

    while (it != ite) {
        if (it->client_fd == client_fd) {
            close(client_fd);
            clients->erase(it);
            break ;
        }
        ++it;
    }
}

// Will execute the last task in the queue and remove it if the recipe is done
void    c_task_queue::exec_task(void) {
    if (_tasks.size() == 0)
        return;
    _tasks.back()->exec();

    if (_tasks.back()->is_over() == true) {
        remove_clients(_clients, _tasks.back()->client_fd);
        delete _tasks.back();
        _tasks.pop();
        return ;
    }
    _tasks.push(_tasks.back());
    _tasks.pop();
}

// Add a new request in c_callback form in the queue
void    c_task_queue::push(std::list<s_request_header> &requests,
                           std::list<s_socket> *clients) {
    c_callback *cb_temp;
    std::list<s_socket>::iterator           it_clients   = clients->begin();
    std::list<s_request_header>::iterator   it_requests  = requests.begin();
    std::list<s_socket>::iterator           ite_clients  = clients->end();
    std::list<s_request_header>::iterator   ite_requests = requests.end();

    while (it_clients != ite_clients && (it_clients->is_header_read == true ||
           it_clients->client_fd == 0))
        ++it_clients;
    while (it_clients != ite_clients && it_requests != ite_requests) {
        cb_temp = new c_callback(*it_clients, *it_requests);
        _tasks.push(cb_temp);
        it_clients->is_header_read = true;
        while (it_clients != ite_clients &&          \
               (it_clients->is_header_read == true || \
               it_clients->client_fd == 0)) {
            ++it_clients;
        }
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
